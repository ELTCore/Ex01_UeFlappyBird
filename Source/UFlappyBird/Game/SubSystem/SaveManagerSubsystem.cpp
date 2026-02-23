// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManagerSubsystem.h"
#include "UFlappyBird/Game/FlappyBirdSaveGame.h"

UFlappyBirdSaveGame* USaveManagerSubsystem::GetCurrentSave() const
{
	return CurrentSaveObject;
}
