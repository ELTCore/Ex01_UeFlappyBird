// Fill out your copyright notice in the Description page of Project Settings.


#include "UISubSystem.h"

UUISubSystem* UUISubSystem::GetInstance()
{
	if (GEngine)
	{
		return GEngine->GetEngineSubsystem<UUISubSystem>();
	}
	return nullptr;
}
