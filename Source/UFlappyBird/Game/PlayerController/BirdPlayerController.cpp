// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UFlappyBird/Game/UI/MainMenuUI.h"

void ABirdPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("ABirdPlayerController::BeginPlay()"));

	bool res = PauseGameAndShowMainMenuUI();
}

bool ABirdPlayerController::PauseGameAndShowMainMenuUI()
{
	if (MainMenuUIClass)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		MainMenuUI = CreateWidget<UMainMenuUI>(this, MainMenuUIClass);
		MainMenuUI->AddToViewport();
		MainMenuUI->OnShow();
		SetShowMouseCursor(true);
		// FInputModeUIOnly Mode;
		// Mode.SetWidgetToFocus(MainMenuUI->TakeWidget());
		SetInputMode(FInputModeUIOnly());
		return true;
	}

	return false;
}
