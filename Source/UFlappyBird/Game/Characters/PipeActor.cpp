// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeActor.h"

#include "PaperSpriteComponent.h"


// Sets default values
APipeActor::APipeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));

	PipesAmount = 3;
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

	for (int i = 0; i < PipesAmount; ++i)
	{
		// 注意：这里使用 NewObject 而非 CreateDefaultSubobject
		FName            pipeCombineName  = *FString::Printf(TEXT("pipCombine_%d"), i);
		USceneComponent* pipeCombineScene = NewObject<USceneComponent>(this, USceneComponent::StaticClass(),
		                                                               pipeCombineName);

		if (pipeCombineScene)
		{
			// 设置组件的创建方式，这能确保它在编辑器中表现得像个正常的组件
			pipeCombineScene->CreationMethod = EComponentCreationMethod::UserConstructionScript;
			pipeCombineScene->SetupAttachment(RootComponent);
			// 必须调用注册，否则编辑器里看不见，且不会渲染
			pipeCombineScene->RegisterComponent();

			//
			FName upPipeName   = *FString::Printf(TEXT("UpPipe_%d"), i);
			FName downPipeName = *FString::Printf(TEXT("DownPipe_%d"), i);

			UPaperSpriteComponent* upPipeComp = NewObject<UPaperSpriteComponent>(
				this, UPaperSpriteComponent::StaticClass(), upPipeName);
			if (upPipeComp)
			{
				upPipeComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;
				upPipeComp->SetupAttachment(pipeCombineScene);
				if (UpPipeSprite)
				{
					upPipeComp->SetSprite(UpPipeSprite);
				}
				upPipeComp->RegisterComponent();
			}


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
}
