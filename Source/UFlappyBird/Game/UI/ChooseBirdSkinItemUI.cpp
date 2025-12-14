// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseBirdSkinItemUI.h"
#include "Components/Button.h"
#include "PaperFlipbook.h"
#include "UFlappyBird/Game/SubSystem/UISubSystem.h"

void UChooseBirdSkinItemUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChooseButton)
	{
		ChooseButton->OnClicked.AddDynamic(this, &UChooseBirdSkinItemUI::OnChooseButtonClicked);
	}
}

void UChooseBirdSkinItemUI::OnChooseButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("UChooseBirdSkinItemUI::OnChooseButtonClicked"));

	if (!BirdFlipbook)
	{
		return;
	}
	if (UUISubSystem* UISubSystem = UUISubSystem::GetInstance())
	{
		UISubSystem->OnBirdSkinChoosed.Broadcast(BirdFlipbook);
	}
	
}
