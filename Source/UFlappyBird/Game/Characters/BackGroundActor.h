// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BackGroundActor.generated.h"

UCLASS()
class UFLAPPYBIRD_API ABackGroundActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABackGroundActor();
	void ChangeBackgroundSprite();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Background")
	class UPaperSpriteComponent* RenderBgImgComponent;
	// 资产
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Background")
	class UPaperSprite* DaySprite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Background")
	class UPaperSprite* NightSprite;

	// 随机切换背景图
	float CurrentTimeAccumulate;
	float MaxTimeToChangeBackSprite;
	int32 CurRandIndex;
	TArray<class UPaperSprite*> BackGroundSprites;
	void  RandBackgroundSprite();
};
