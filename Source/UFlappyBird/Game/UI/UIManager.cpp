// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

#include "Blueprint/UserWidget.h"

UUserWidget* UUIManager::ShowScreen(TSubclassOf<UUserWidget> ScreenlClass)
{
	if (CurrentScreen)
	{
		CurrentScreen->RemoveFromParent();
		CurrentScreen = nullptr;
	}

	CurrentScreen = CreateWidget<UUserWidget>(GetWorld(), ScreenlClass);
	CurrentScreen->AddToViewport();
	
	return CurrentScreen;
}
