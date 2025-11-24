// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BirdHud.generated.h"

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API ABirdHud : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<class UStartButton> StartButtonClass;

	UPROPERTY()
	UStartButton* StartButton;
};
