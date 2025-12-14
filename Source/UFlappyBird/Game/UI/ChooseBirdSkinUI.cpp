// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseBirdSkinUI.h"

#include "UFlappyBird/Game/SubSystem/UISubSystem.h"

void UChooseBirdSkinUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);

	if (UUISubSystem* UISubSystem = UUISubSystem::GetInstance())
	{
		UISubSystem->OnBirdSkinChoosed.AddDynamic(this, &UChooseBirdSkinUI::OnBirdSkinChoosed);
	}
}

void UChooseBirdSkinUI::OnShow()
{
	Super::OnShow();
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->SetInputMode(FInputModeUIOnly());
		PC->SetShowMouseCursor(true);
		this->SetFocus();
	}
}


void UChooseBirdSkinUI::SetupBinding()
{
		
}

void UChooseBirdSkinUI::OnBirdSkinChoosed(UPaperFlipbook* BirdFlipbook)
{
	UE_LOG(LogTemp, Log, TEXT("OnBirdSkinChoosed"));
	
	this->OnHide();
}
