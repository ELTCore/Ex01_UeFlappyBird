// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUI.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UMainMenuUI::NativeConstruct()
{
	Super::NativeConstruct();


	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenuUI::OnStartButtonClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuUI::OnQuitButtonClicked);
	}
	
}

void UMainMenuUI::OnStartButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Start Game"));
	this->OnHide();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->SetInputMode(FInputModeGameOnly());
	PC->SetShowMouseCursor(false);
	
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UMainMenuUI::OnQuitButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("QuitButton Clicked."));
	
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
