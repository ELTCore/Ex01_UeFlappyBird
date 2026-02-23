// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"

#include "UFlappyBird/Game/Characters/Bird.h"
#include "UFlappyBird/Game/GameState/BirdGameStateBase.h"
#include "UFlappyBird/Game/HUD/BirdHud.h"

ADefaultGameMode::ADefaultGameMode()
{
	DefaultPawnClass = ABird::StaticClass();
	// HUDClass = ABirdHud::StaticClass();
	GameStateClass = ABirdGameStateBase::StaticClass();
}
