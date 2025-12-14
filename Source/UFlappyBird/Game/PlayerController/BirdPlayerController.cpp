// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPlayerController.h"

#include "PaperFlipbookComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UFlappyBird/Game/Characters/Bird.h"
#include "UFlappyBird/Game/UI/MainMenuUI.h"
#include "UFlappyBird/Game/SubSystem/UISubSystem.h"

void ABirdPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("ABirdPlayerController::BeginPlay()"));

	bool res = PauseGameAndShowMainMenuUI();

	if (UUISubSystem* UISubSystem = UUISubSystem::GetInstance())
	{
		UISubSystem->OnBirdSkinChoosed.AddDynamic(this, &ABirdPlayerController::OnBirdSkinChoosed);
	}
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

void ABirdPlayerController::OnBirdSkinChoosed(UPaperFlipbook* BirdSkinChoosed)
{
	SwitchBirdSkin = BirdSkinChoosed;
	ABird* Bird = Cast<ABird>(this->GetPawn());
	if (Bird)
	{
		// @Todo bug, 切换为与bird初始FlipBook不一致的FLipBook后导致其动不了了
		Bird->BirdFlipbookComponent->SetFlipbook(SwitchBirdSkin);
		Bird->BirdFlipbookComponent->SetSimulatePhysics(true); // 开启物理模拟
	}
	
}
