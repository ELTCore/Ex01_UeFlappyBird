// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UFlappyBird/Game/Characters/Bird.h"
#include "UFlappyBird/Game/SubSystem/BirdEventSubSystem.h"
#include "UFlappyBird/Game/UI/MainMenuUI.h"
#include "UFlappyBird/Game/SubSystem/UISubSystem.h"

void ABirdPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("ABirdPlayerController::BeginPlay()"));

	bool res = PauseGameAndShowMainMenuUI();

	if (UUISubSystem* UISubSystem = UUISubSystem::GetInstance())
	{
		UISubSystem->OnBirdSkinChoosed.AddDynamic(this, &ABirdPlayerController::OnBirdSkinChoosed);
	}

	// 添加 Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	//
	if (UBirdEventSubSystem* BirdEventSubSystem = UBirdEventSubSystem::GetInstance())
	{
		BirdEventSubSystem->OnBirdDeaded.AddDynamic(this, &ABirdPlayerController::OnBirdDeaded);
	}
}

bool ABirdPlayerController::PauseGameAndShowMainMenuUI()
{
	if (MainMenuUIClass)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		MainMenuUI = CreateWidget<UMainMenuUI>(this, MainMenuUIClass);
		MainMenuUI->AddToViewport();
		MainMenuUI->OnShow();
		SetShowMouseCursor(true);
		// FInputModeUIOnly Mode;
		// Mode.SetWidgetToFocus(MainMenuUI->TakeWidget());
		SetInputMode(FInputModeUIOnly());
		return true;
	}

	return false;
}

void ABirdPlayerController::OnBirdSkinChoosed(UPaperFlipbook* BirdSkinChoosed)
{
	SwitchBirdSkin = BirdSkinChoosed;
	ABird* Bird    = Cast<ABird>(this->GetPawn());
	if (Bird)
	{
		Bird->BirdFlipbookComponent->SetFlipbook(SwitchBirdSkin);
		Bird->BirdFlipbookComponent->SetSimulatePhysics(true); // 开启物理模拟
	}
}

void ABirdPlayerController::OnBirdDeaded()
{
	if (GetWorld())
	{
		// 获取当前关卡的名称（字符串格式）
		FString CurrentLevelName = GetWorld()->GetMapName();

		// 在编辑器模式下（PIE），关卡名可能包含前缀（如 UEDPIE_0_），OpenLevel 可以自动处理
		UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
	}
}

void ABirdPlayerController::OnEscAction(const FInputActionValue& InputActionValue)
{
	PauseGameAndShowMainMenuUI();
}

void ABirdPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 绑定 Input Action
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// ETriggerEvent::Triggered 表示按键被触发（按下或持续按住，取决于 IA 配置）
		EnhancedInputComponent->BindAction(EscAction, ETriggerEvent::Triggered, this,
		                                   &ABirdPlayerController::OnEscAction);
	}
}
