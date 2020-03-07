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
	/////////functions/////////
	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:

	UPROPERTY(EditAnywhere)
	TArray<class APlatformTrigger*> ActivePlatformTrigger;

protected:
	virtual void Tick(float DeltaTime) override;

	FVector GloablTargetLocation;
	FVector GloablStartLoacation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ActiveTrigger = 0;
};
