// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipeActor.generated.h"

UCLASS()
class UFLAPPYBIRD_API APipeActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APipeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//
	void PipeMove(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe")
	class UPaperSprite* UpPipeSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe")
	class UPaperSprite* DownPipeSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe",
		meta = (ClampMin="0", UIMin="0", ClampMax="255", UIMax="255"))
	int32 PipesAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe",
		meta = (ClampMin="0", UIMin="0", ClampMax="999", UIMax="999"))
	int32 PipeMaxHorizonGap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe",
		meta = (ClampMin="0", UIMin="0", ClampMax="999", UIMax="999"))
	int32 PipeMinHorizonGap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe",
		meta = (ClampMin="0", UIMin="0", ClampMax="999", UIMax="999"))
	int32 PipeMaxVerticalGap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe",
		meta = (ClampMin="0", UIMin="0", ClampMax="999", UIMax="999"))
	int32 PipeMinVerticalGap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe",
		meta = (ClampMin="-999", UIMin="-999", ClampMax="999", UIMax="999"))
	int32 PipeMinVerticalOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe",
		meta = (ClampMin="-999", UIMin="-999", ClampMax="999", UIMax="999"))
	int32 PipeMaxVerticalOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe")
	int32 PipeMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Pipe");
	int32 PipeStartRegionPositionX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pipe");
	class UBoxComponent* PipeStartRegion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pipe");
	int32 PipeResetRegionPositionX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pipe");
	class UBoxComponent* PipeResetRegion;

	UPROPERTY()
	TArray<USceneComponent*> PipeSceneArray;
};
