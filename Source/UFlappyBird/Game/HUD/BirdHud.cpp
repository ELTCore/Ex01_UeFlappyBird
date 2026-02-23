// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdHud.h"

#include "Kismet/GameplayStatics.h"
#include "UFlappyBird/Game/GameState/BirdGameStateBase.h"

void ABirdHud::BeginPlay()
{
	Super::BeginPlay();

	BirdGameState = Cast<ABirdGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
}

void ABirdHud::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ABirdHud::DrawHUD()
{
	Super::DrawHUD();

	DrawGameScoreToScreen();
}

void ABirdHud::DrawGameScoreToScreen()
{
	if (!BirdGameState)
	{
		return;
	}

	int32 curScore = BirdGameState->GetCurrentScore();
	DrawText(FString::Printf(TEXT("Current Score: %d"), curScore), FLinearColor::Red, 20, 20);
}
