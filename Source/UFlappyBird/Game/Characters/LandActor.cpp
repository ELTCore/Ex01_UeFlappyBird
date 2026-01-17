// Fill out your copyright notice in the Description page of Project Settings.


#include "LandActor.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
ALandActor::ALandActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent        = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RenderLandsComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RenderLands"));

	RenderLandsComponent->SetupAttachment(RootComponent);


	MoveSpeedX      = -10.0;
	LandActorAmount = 3;
	LandSprite      = nullptr;
}

// #pragma optimize("", off)
void ALandActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	for (USceneComponent* Comp : LandSceneArray)
	{
		if (Comp)
		{
			Comp->DestroyComponent();
		}
	}
	LandSceneArray.Empty();

	LandSceneArray.Reserve(LandActorAmount);
	if (LandSprite && RenderLandsComponent)
	{
		FVector landSize  = LandSprite->GetRenderBounds().GetBox().GetSize();
		double  curOffset = 0;
		for (int i = 0; i < LandActorAmount; ++i)
		{
			FName                  landName  = *FString::Printf(TEXT("landScene_%d"), i);
			UPaperSpriteComponent* landScene = NewObject<UPaperSpriteComponent>(
				this, UPaperSpriteComponent::StaticClass(), landName);
			if (landScene)
			{
				landScene->CreationMethod = EComponentCreationMethod::UserConstructionScript;
				landScene->SetupAttachment(RenderLandsComponent);
				if (landScene)
				{
					landScene->SetSprite(LandSprite);
				}
				landScene->SetRelativeLocation(FVector(curOffset, 0.0, 0.0));
				landScene->RegisterComponent();
				curOffset += landSize.X;

				LandSceneArray.Add(landScene);
			}
		}
	}
}
// #pragma optimize("", on)

// Called when the game starts or when spawned
void ALandActor::BeginPlay()
{
	Super::BeginPlay();
}

// #pragma optimize("", off)
void ALandActor::LandMove(float DeltaTime)
{
	// if (!LandSprite || !RenderLand || !RenderNextLand)
	// {
	// 	return;
	// }
	if (!LandSprite || !RenderLandsComponent)
	{
		return;
	}

	double spriteWidth = LandSprite->GetRenderBounds().GetBox().GetSize().X;
	for (auto landScene : LandSceneArray)
	{
		if (!landScene)
		{
			continue;
		}
		landScene->AddRelativeLocation(FVector(MoveSpeedX * DeltaTime, 0, 0));

		double curRelativeX = landScene->GetRelativeLocation().X;
		if (curRelativeX < -spriteWidth)
		{
			landScene->SetRelativeLocation(FVector(spriteWidth * (LandSceneArray.Num() - 1) - 1, 0, 0));
		}
	}

	// RenderLand->AddRelativeLocation(FVector(MoveSpeedX * DeltaTime, 0, 0));
	// RenderNextLand->AddRelativeLocation(FVector(MoveSpeedX * DeltaTime, 0, 0));
	//
	// float spriteWidth = LandSprite->GetRenderBounds().GetBox().GetSize().X;
	//
	// float CurRelativeRenderlandX = RenderLand->GetRelativeLocation().X;
	// if (CurRelativeRenderlandX < -spriteWidth)
	// {
	// 	RenderLand->SetRelativeLocation(FVector(spriteWidth, 0, 0));
	// }
	// float CurRelativeRenderNextlandX = RenderNextLand->GetRelativeLocation().X;
	// if (CurRelativeRenderNextlandX < -spriteWidth)
	// {
	// 	RenderNextLand->SetRelativeLocation(FVector(spriteWidth, 0, 0));
	// }
}
// #pragma optimize("", on)

// Called every frame
void ALandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LandMove(DeltaTime);
}
