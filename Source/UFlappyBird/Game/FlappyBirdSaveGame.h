// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FlappyBirdSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FPlayerScoreData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HighScore = 0;
};
/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API UFlappyBirdSaveGame : public USaveGame
{
	GENERATED_BODY()
};
