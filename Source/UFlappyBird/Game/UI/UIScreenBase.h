// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIScreenBase.generated.h"

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API UUIScreenBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void OnShow();

	UFUNCTION(BlueprintCallable)
	virtual void OnHide();
	
};
