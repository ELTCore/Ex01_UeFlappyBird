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

	UPROPERTY(EditDefaultsOnly, Category="BirdSkin")
	class UPaperFlipbook* SwitchBirdSkin;

private:
	UPROPERTY()
	UMainMenuUI* MainMenuUI;

	UFUNCTION()
	bool PauseGameAndShowMainMenuUI();

	UFUNCTION()
	void OnBirdSkinChoosed(class UPaperFlipbook* BirdSkinChoosed);
};
