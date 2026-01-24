// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeActor.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
APipeActor::APipeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent   = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	PipeStartRegion = CreateDefaultSubobject<UBoxComponent>(TEXT("PipeStartRegion"));
	PipeResetRegion = CreateDefaultSubobject<UBoxComponent>(TEXT("PipeResetRegion"));
	PipeStartRegion->SetupAttachment(RootComponent);
	PipeResetRegion->SetupAttachment(RootComponent);
#if WITH_EDITORONLY_DATA
	PipeStartRegion->bIsEditorOnly       = true;
	PipeStartRegion->bVisualizeComponent = true;
	PipeResetRegion->bIsEditorOnly       = true;
	PipeResetRegion->bVisualizeComponent = true;
#endif
	PipeStartRegion->SetHiddenInGame(true);
	PipeResetRegion->SetHiddenInGame(true);

	PipesAmount           = 3;
	PipeMinHorizonGap     = 100;
	PipeMaxHorizonGap     = 300;
	PipeMinVerticalGap    = 500;
	PipeMaxVerticalGap    = 800;
	PipeMinVerticalOffset = -300;
	PipeMaxVerticalOffset = 300;

	PipeStartRegionPositionX = 500;
	PipeResetRegionPositionX = -500;

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

	/*
	 *  处理初始管道位置
	 */
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

	/*
	 * 在蓝图编辑器界面绘制管道刷新位置与重置位置 
	 */
	float lastPipePosX       = PipeSceneArray.Last()->GetRelativeLocation().X;
	PipeStartRegionPositionX = lastPipePosX;
	PipeStartRegion->SetRelativeLocation(FVector(PipeStartRegionPositionX, 0.0f, 0.0f));
	PipeResetRegion->SetRelativeLocation(FVector(PipeResetRegionPositionX, 0.0f, 0.0f));
}

// Called every frame
void APipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PipeMove(DeltaTime);
}


#pragma optimize("", off)
void APipeActor::PipeMove(float DeltaTime)
{
	// @Todo 需要解决不断重置管道位置后，管道位置的横向偏移量可能越来越离谱的问题，问题产生原因：左侧重置线是固定的，右侧重置的位置则产生一定随机

	for (int i = 0; i < PipeSceneArray.Num(); ++i)
	{
		USceneComponent* pipeCombineScene = PipeSceneArray[i];

		if (pipeCombineScene)
		{
			pipeCombineScene->AddRelativeLocation(FVector(DeltaTime * PipeMoveSpeed, 0.0, 0.0));

			float curX = pipeCombineScene->GetRelativeLocation().X;
			if (curX < PipeResetRegionPositionX)
			{
				int32 verticalGap   = FMath::RandRange(PipeMinVerticalGap, PipeMaxVerticalGap);
				int32 randHorGap    = FMath::RandRange(PipeMinHorizonGap, PipeMaxHorizonGap);
				int32 randHorOffset = randHorGap * FMath::RandRange(-0.5, 0.5);
				int32 horOffset     = PipeStartRegionPositionX + randHorOffset;

				USceneComponent* upPipeScene = pipeCombineScene->GetChildComponent(0); // 有更可读的写法吗？
				if (upPipeScene)
				{
					upPipeScene->SetRelativeLocation(FVector(0.0, 0.0, -verticalGap * 0.5));
				}
				USceneComponent* downPipeScene = pipeCombineScene->GetChildComponent(1); // 
				if (downPipeScene)
				{
					downPipeScene->SetRelativeLocation(FVector(0.0, 0.0, verticalGap * 0.5));
				}

				pipeCombineScene->SetRelativeLocation(FVector(horOffset, 0.0, 0.0));

			}
		}
	}
}
#pragma optimize("", on)
