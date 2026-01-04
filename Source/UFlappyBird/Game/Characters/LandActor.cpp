// Fill out your copyright notice in the Description page of Project Settings.


#include "LandActor.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
ALandActor::ALandActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent  = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RenderLand     = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("RenderLand"));
	RenderNextLand = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("NextLand"));
	//
	RenderLand->SetupAttachment(RootComponent);
	RenderNextLand->SetupAttachment(RootComponent);

	MoveSpeedX = -10.0;
	LandSprite = nullptr;
}

void ALandActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (LandSprite && RenderNextLand && RenderLand)
	{
		RenderLand->SetSprite(LandSprite);
		RenderNextLand->SetSprite(LandSprite);

		// 初始位置
		FVector landSize = LandSprite->GetRenderBounds().GetBox().GetSize();
		RenderLand->SetRelativeLocation(FVector::ZeroVector);
		RenderNextLand->SetRelativeLocation(FVector(landSize.X, 0, 0));
	}
}

// Called when the game starts or when spawned
void ALandActor::BeginPlay()
{
	Super::BeginPlay();
	
}

#pragma optimize("", off)
void ALandActor::LandMove(float DeltaTime)
{
	if (!LandSprite || !RenderLand || !RenderNextLand)
	{ 
		return;
	}

	RenderLand->AddRelativeLocation(FVector(MoveSpeedX*DeltaTime, 0,0));
	RenderNextLand->AddRelativeLocation(FVector(MoveSpeedX*DeltaTime, 0,0));

	float spriteWidth = LandSprite->GetRenderBounds().GetBox().GetSize().X;
	
	float CurRelativeRenderlandX = RenderLand->GetRelativeLocation().X;
	 if (CurRelativeRenderlandX < -spriteWidth)
	{
		RenderLand->SetRelativeLocation(FVector(spriteWidth, 0, 0));
	}
	float CurRelativeRenderNextlandX = RenderNextLand->GetRelativeLocation().X;
	if (CurRelativeRenderNextlandX < -spriteWidth)
	{
		RenderNextLand->SetRelativeLocation(FVector(spriteWidth, 0, 0));
	}
	
}
#pragma optimize("", on)

// Called every frame
void ALandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LandMove(DeltaTime);
}
