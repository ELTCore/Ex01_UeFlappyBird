// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseBirdSkinUI.h"

void UChooseBirdSkinUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);

	
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
