// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeActor.h"

#include "PaperSpriteComponent.h"


// Sets default values
APipeActor::APipeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));

	PipesAmount           = 3;
	PipeMinHorizonGap     = 100;
	PipeMaxHorizonGap     = 300;
	PipeMinVerticalGap    = 500;
	PipeMaxVerticalGap    = 800;
	PipeMinVerticalOffset = -300;
	PipeMaxVerticalOffset = 300;

	ResetLineLeft = -500;
	ResetLineRight = 500;
	
	PipeMoveSpeed = -10;
}

// Called when the game starts or when spawned
void APipeActor::BeginPlay()
{
	Super::BeginPlay();
}

void APipeActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	for (USceneComponent* Comp : PipeSceneArray)
	{
		if (Comp)
		{
			Comp->DestroyComponent();
		}
	}
	PipeSceneArray.Empty();
	PipeSceneArray.Reserve(PipesAmount);
	
	int32 accumulateHorGap = 0;
	for (int i = 0; i < PipesAmount; ++i)
	{
		// 注意：这里使用 NewObject 而非 CreateDefaultSubobject
		FName            pipeCombineName  = *FString::Printf(TEXT("pipCombine_%d"), i);
		USceneComponent* pipeCombineScene = NewObject<USceneComponent>(this, USceneComponent::StaticClass(),
		                                                               pipeCombineName);
		if (pipeCombineScene)
		{
			pipeCombineScene->CreationMethod = EComponentCreationMethod::UserConstructionScript;
			pipeCombineScene->SetupAttachment(RootComponent);
			int32 verticalOffset = FMath::RandRange(PipeMinVerticalOffset, PipeMaxVerticalOffset);
			accumulateHorGap += FMath::RandRange(PipeMinHorizonGap, PipeMaxHorizonGap);
			pipeCombineScene->SetRelativeLocation(FVector(accumulateHorGap, 0.0, verticalOffset));
			pipeCombineScene->RegisterComponent();

			FName                  upPipeName = *FString::Printf(TEXT("UpPipe_%d"), i);
			UPaperSpriteComponent* upPipeComp = NewObject<UPaperSpriteComponent>(
				this, UPaperSpriteComponent::StaticClass(), upPipeName);
			int32 verticalGap = FMath::RandRange(PipeMinVerticalGap, PipeMaxVerticalGap);
			if (upPipeComp)
			{
				upPipeComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;
				upPipeComp->SetupAttachment(pipeCombineScene);
				if (UpPipeSprite)
				{
					upPipeComp->SetSprite(UpPipeSprite);
				}
				upPipeComp->SetRelativeLocation(FVector(0.0, 0.0, -verticalGap * 0.5));
				upPipeComp->RegisterComponent();
			}

			FName                  downPipeName = *FString::Printf(TEXT("DownPipe_%d"), i);
			UPaperSpriteComponent* downPipeComp = NewObject<UPaperSpriteComponent>(
				this, UPaperSpriteComponent::StaticClass(), downPipeName);
			if (downPipeComp)
			{
				downPipeComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;
				downPipeComp->SetupAttachment(pipeCombineScene);
				if (DownPipeSprite)
				{
					downPipeComp->SetSprite(DownPipeSprite);
				}
				downPipeComp->SetRelativeLocation(FVector(0.0, 0.0, verticalGap * 0.5));
				downPipeComp->RegisterComponent();
			}
			//
			PipeSceneArray.Add(pipeCombineScene);
		}
	}
}

// Called every frame
void APipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PipeMove();
}

void APipeActor::PipeMove()
{
	
}
