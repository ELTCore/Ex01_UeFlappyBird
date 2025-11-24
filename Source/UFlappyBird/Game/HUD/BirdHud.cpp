// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdHud.h"

#include "StartButton.h"


void ABirdHud::BeginPlay()
{
	Super::BeginPlay();

	if (StartButtonClass)
	{
		StartButton = CreateWidget<UStartButton>(GetWorld(), StartButtonClass);
		if (StartButton)
		{
			StartButton->AddToViewport();
		}
	}
}

void ABirdHud::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}
