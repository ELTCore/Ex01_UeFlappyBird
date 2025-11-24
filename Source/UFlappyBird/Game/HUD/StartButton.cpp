// Fill out your copyright notice in the Description page of Project Settings.


#include "StartButton.h"

#include "Components/Button.h"


bool UStartButton::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UStartButton::OnClicked);
	}
	
	return true;
}

void UStartButton::OnClicked()
{
	UE_LOG(LogTemp, Log, TEXT("UStartButton::OnClicked"));
}
