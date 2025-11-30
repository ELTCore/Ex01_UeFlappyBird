// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UIManager.generated.h"

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API UUIManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	UUserWidget* ShowScreen(TSubclassOf<UUserWidget> ScreenlClass);

private:
	UPROPERTY()
	UUserWidget* CurrentScreen;
};
