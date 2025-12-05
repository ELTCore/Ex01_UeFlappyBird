// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BirdPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API ABirdPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UMainMenuUI> MainMenuUIClass;


private:
	UPROPERTY()
	UMainMenuUI* MainMenuUI;

	UFUNCTION()
	bool PauseGameAndShowMainMenuUI();
};
