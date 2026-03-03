// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdEventSubSystem.h"

UBirdEventSubSystem* UBirdEventSubSystem::GetInstance()
{
	if (GEngine)
	{
		return GEngine->GetEngineSubsystem<UBirdEventSubSystem>();
	}
	return nullptr;
}
