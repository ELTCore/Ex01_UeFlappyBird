// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartButton.generated.h"

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API UStartButton : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UFUNCTION()
	void OnClicked();
};
