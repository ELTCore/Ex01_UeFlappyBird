// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "UISubSystem.generated.h"

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API UUISubSystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	static UUISubSystem* GetInstance();
};
