// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandActor.generated.h"


UCLASS()
class UFLAPPYBIRD_API ALandActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALandActor();
	//
	void OnConstruction(const FTransform& Transform) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 
	void LandMove(float DeltaTime);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="LandSprite")
	class USceneComponent* RenderLandsComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LandSprite")
	class UPaperSprite* LandSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LandSprite")
	float MoveSpeedX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LandSprite")
	TArray<class UPaperSpriteComponent*> LandSceneArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LandSprite",
		meta = (ClampMin="1", UIMin="1", ClampMax="256", UIMax="256"))
	int32 LandActorAmount;
	
};
