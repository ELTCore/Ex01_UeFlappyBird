// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "BirdEventSubSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnBirdDeaded
);

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API UBirdEventSubSystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	static UBirdEventSubSystem* GetInstance();
	/*
	* SIGNALS
	*/
	UPROPERTY(BlueprintAssignable, Category = "SIGNALS")
	FOnBirdDeaded OnBirdDeaded;
};
