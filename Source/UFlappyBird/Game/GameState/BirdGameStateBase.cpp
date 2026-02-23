// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdGameStateBase.h"

ABirdGameStateBase::ABirdGameStateBase()
{
}

void ABirdGameStateBase::AddScore()
{
	++CurrentScore;
}

void ABirdGameStateBase::ResetScore()
{
	CurrentScore = 0;
}

int32 ABirdGameStateBase::GetCurrentScore()
{

	return CurrentScore;
}
