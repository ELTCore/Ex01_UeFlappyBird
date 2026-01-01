// Fill out your copyright notice in the Description page of Project Settings.


#include "BackGroundActor.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
ABackGroundActor::ABackGroundActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 组件
	RootComponent        = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));     // 根组件
	RenderBgImgComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BgComp")); // 背景图片组件
	DaySprite            = nullptr;
	NightSprite          = nullptr;
	// 组件依附关系
	RenderBgImgComponent->SetupAttachment(RootComponent);
	//背景图处理
	CurRandIndex              = -1;
	CurrentTimeAccumulate     = 0.0f;
	MaxTimeToChangeBackSprite = FMath::RandRange(5.f, 10.f);
}


// Called when the game starts or when spawned
void ABackGroundActor::BeginPlay()
{
	Super::BeginPlay();
	// DaySprite   = LoadObject<UPaperSprite>(nullptr, TEXT(""));
	if (DaySprite)
	{
		BackGroundSprites.Push(DaySprite);
	}

	// NightSprite = LoadObject<UPaperSprite>(nullptr, TEXT(""));
	if (NightSprite)
	{
		BackGroundSprites.Push(NightSprite);
	}
	ChangeBackgroundSprite();
}

// Called every frame
void ABackGroundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
	CurrentTimeAccumulate += DeltaTime;
	if (CurrentTimeAccumulate > MaxTimeToChangeBackSprite)
	{
		ChangeBackgroundSprite();
		CurrentTimeAccumulate     = 0.0f;
		MaxTimeToChangeBackSprite = FMath::RandRange(4.0f, 8.0f);
	}
}
#pragma optimize("", off)
void ABackGroundActor::ChangeBackgroundSprite()
{
	int listSize = BackGroundSprites.Num() ;
	if (listSize > 0)
	{
		CurRandIndex = (CurRandIndex + 1) % listSize;
		RenderBgImgComponent->SetSprite(BackGroundSprites[CurRandIndex]);
	}
}
#pragma optimize("", on)
