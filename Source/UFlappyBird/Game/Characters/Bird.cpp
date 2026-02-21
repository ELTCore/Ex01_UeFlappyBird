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
#include "PipeActor.h"
#include "UFlappyBird/Game/PlayerController/BirdPlayerController.h"

// Sets default values
ABird::ABird()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// 组件构建
	RootComponent           = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	BirdFlipbookComponent   = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BirdFlipbookComponent"));
	SpringArm               = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	BirdMainCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("BirdMainCameraComponent"));
	SphereComponent         = CreateDefaultSubobject<USphereComponent>(TEXT("USphereComponent"));
	// 组件依附
	if (BirdFlipbookComponent)
	{
		BirdFlipbookComponent->SetupAttachment(RootComponent);
	}
	SpringArm->SetupAttachment(RootComponent);
	BirdMainCameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	if (SphereComponent && BirdFlipbookComponent)
	{
		SphereComponent->SetupAttachment(BirdFlipbookComponent);
		// SphereComponent->SetCollisionObjectType(ECC_OverlapAll_Deprecated);
		SphereComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	}
	// 组件设置
	SpringArm->bDoCollisionTest = false;
	BirdMainCameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
	BirdMainCameraComponent->OrthoWidth = 1000.f;
	// SpringArm->SetRelativeRotation(FRotator(0.0, -90, 0.0));


	// 输入映射
	InputMapping = nullptr;
	FlyAction    = nullptr;
}

void ABird::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (DefaultBirdFlipbook && BirdFlipbookComponent)
	{
		BirdFlipbookComponent->SetFlipbook(DefaultBirdFlipbook);
		BirdFlipbookComponent->SetSimulatePhysics(true); // 开启物理模拟
	}

	if (SpringArm)
	{
		UE_LOG(LogTemp, Log, TEXT("SpringArm->bDoCollisionTest = %s"),
		       SpringArm->bDoCollisionTest ? TEXT("true") : TEXT("false"));
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
	if (BirdFlipbookComponent)
	{
		BirdFlipbookComponent->SetSimulatePhysics(true); // 开启物理模拟

		// 为小鸟组件添加Hit事件
		BirdFlipbookComponent->SetNotifyRigidBodyCollision(true); // 在开启物理模拟后允许Hit事件执行
		BirdFlipbookComponent->SetCollisionObjectType(ECC_Pawn);  // ObjectType修改为Pawn 与其它物体之间是阻挡关系
		BirdFlipbookComponent->OnComponentHit.AddDynamic(this, &ABird::OnComponentHitEvent);
	}
	if (!InitializePlayerInput())
		return;

	if (SphereComponent)
	{
		// 为组件 Shperecomponent 设置 Overlap 事件
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABird::OnComponentBeginOverlapEvent);
	}
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpringArm)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow,
		                                 FString::Printf(TEXT("Current Arm Length: %f"), SpringArm->TargetArmLength));
	}
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
	BirdFlipbookComponent->AddImpulse(FVector(0, 0, FlyImpluse)); // 开启物理模拟才有效果
}

void ABird::OnComponentBeginOverlapEvent(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult&          SweepResult)
{
	if (APipeActor* PipeActor = Cast<APipeActor>(OtherActor))
	{
		UE_LOG(LogTemp, Display, TEXT(__FUNCSIG__));
	}
}

void ABird::OnComponentHitEvent(class UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                class UPrimitiveComponent* OtherComp, FVector    NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT(__FUNCSIG__));
}
