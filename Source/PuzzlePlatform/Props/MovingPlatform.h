// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
public:
	UPROPERTY(EditInstanceOnly, Category = "Move Option", Meta = (MakeEditWidget = "true"))
	FVector TargetLocationOffset;

	UPROPERTY(EditInstanceOnly, Category = "Move Option")
	float MoveSpeed;

private:
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
};
