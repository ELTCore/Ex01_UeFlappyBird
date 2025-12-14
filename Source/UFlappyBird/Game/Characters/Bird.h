// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

UCLASS()
class UFLAPPYBIRD_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();
	//
	void OnConstruction(const FTransform& Transform) override;
	bool InitializePlayerInput() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 组件
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bird")
	class UPaperFlipbookComponent* BirdFlipbookComponent; // 鸟
	class USpringArmComponent*     SpringArm;             // 相机弹簧臂
	class UCameraComponent*        MainCemera;            // 主相机
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent*        ShpereComponent;       // 碰撞箱
	// 资产
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bird")
	class UPaperFlipbook* DefaultBirdFlipbook; // 鸟

	// 输入映射
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	class UInputMappingContext* InputMapping;

	// Fly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	class UInputAction* FlyAction;
	void OnFlyAction(const FInputActionValue& InputActionValue);

};
