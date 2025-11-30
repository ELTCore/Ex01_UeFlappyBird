// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
ABird::ABird()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	// 组件构建
	RootComponent         = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	BirdFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BirdFlipbookComponent"));
	SpringArm             = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	MainCemera            = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCemera"));
	ShpereComponent       = CreateDefaultSubobject<USphereComponent>(TEXT("USphereComponent"));
	// 组件依附
	BirdFlipbookComponent->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(RootComponent);
	MainCemera->SetupAttachment(SpringArm);
	ShpereComponent->SetupAttachment(RootComponent);
	// 组件设置
	SpringArm->bDoCollisionTest = false;
	MainCemera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	MainCemera->OrthoWidth = 1000.f;
	SpringArm->SetRelativeRotation(FRotator(0.0, -90, 0.0));

	// 输入映射
	InputMapping = nullptr;
	FlyAction    = nullptr;

	
	
}

void ABird::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (BirdFlipbook && BirdFlipbookComponent)
	{
		BirdFlipbookComponent->SetFlipbook(BirdFlipbook);
		BirdFlipbookComponent->SetSimulatePhysics(true); // 开启物理模拟
	}

}


bool ABird::InitializePlayerInput() const
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC)
	{
		return false;
	}
	ULocalPlayer*                       CurPlayer = PC->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsys    = nullptr;
	if (CurPlayer)
	{
		Subsys = CurPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	}
	if (CurPlayer && Subsys)
	{
		Subsys->AddMappingContext(InputMapping, 0);
	}

	return true;
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();

	if (InitializePlayerInput())
		return;

}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (EIC)
	{
		EIC->BindAction(FlyAction, ETriggerEvent::Started, this, &ABird::OnFlyAction);
	}

	UE_LOG(LogTemp, Display, TEXT("Bird::SetupPlayerInputComponent End"));
}

void ABird::OnFlyAction(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Display, TEXT("OnFlyAction"));
	BirdFlipbookComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
	BirdFlipbookComponent->AddImpulse(FVector(0, 0, 2500)); // 开启物理模拟才有效果

}
