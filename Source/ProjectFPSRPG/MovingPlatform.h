// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFPSRPG_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Speed = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Meta = (MakeEditWidget = true))
	FVector TargetLocation;

protected:
	virtual void Tick(float DeltaTime) override;

	FVector GloablTargetLocation;
	FVector GloablStartLoacation;
};
