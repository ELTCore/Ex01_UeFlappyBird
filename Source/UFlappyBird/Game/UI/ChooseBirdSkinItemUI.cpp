// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseBirdSkinItemUI.h"
#include "Components/Button.h"
#include "PaperFlipbook.h"

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

}
