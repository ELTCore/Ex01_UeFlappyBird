// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BirdGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API ABirdGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	ABirdGameStateBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="score")
	int32 CurrentScore = 0;

	//
	void AddScore();
	//
	void ResetScore();
	//
	int32 GetCurrentScore();
	
};
