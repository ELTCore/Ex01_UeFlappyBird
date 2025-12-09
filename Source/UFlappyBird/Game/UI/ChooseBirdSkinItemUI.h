// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChooseBirdSkinItemUI.generated.h"


/**
 * 
 */
UCLASS()
class UFLAPPYBIRD_API UChooseBirdSkinItemUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text")
	FString Name = TEXT("Default Name");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text")
	FText Description = FText::FromString(TEXT("Default description text."));

	UPROPERTY(meta = (BindWidget))
	class UButton* ChooseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BirdFlipbook")
	class UPaperFlipbookComponent* BirdFlipbook;

	UFUNCTION()
	void OnChooseButtonClicked();


};
