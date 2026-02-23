// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// 外部调用的接口
	void SavePlayerData();
	void LoadPlayerData();

	// 获取数据（单例风格访问）
	UFUNCTION(BlueprintPure)
	class UFlappyBirdSaveGame* GetCurrentSave() const;

private:
	UPROPERTY()
	class UFlappyBirdSaveGame* CurrentSaveObject = nullptr;

	FString SlotName = TEXT("PlayerSaveSlot_0");
};
