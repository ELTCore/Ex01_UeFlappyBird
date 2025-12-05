// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIScreenBase.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API UMainMenuUI : public UUIScreenBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* SkinButton;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UChooseBirdSkinUI> ChooseBirdSkinUIClass;
	
private:
	UFUNCTION()
	void OnStartButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnSkinButtonClicked();

	UPROPERTY()
	UChooseBirdSkinUI* ChooseBirdSkinUI;
};
