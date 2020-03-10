// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPSRPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFPSRPG_API UFPSRPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFPSRPGGameInstance(const FObjectInitializer & ObjectInitializer);

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Adress);

//public:
//
//	virtual void Init() override;

};
