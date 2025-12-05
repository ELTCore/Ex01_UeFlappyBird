// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIScreenBase.h"
#include "Blueprint/UserWidget.h"
#include "ChooseBirdSkinUI.generated.h"

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API UChooseBirdSkinUI : public UUIScreenBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void OnShow() override;
};
