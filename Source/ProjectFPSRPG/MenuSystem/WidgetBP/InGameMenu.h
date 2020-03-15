// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"

#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFPSRPG_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* InMenuInterface);

	void Setup();

private:
	IMenuInterface* MenuInterfacePtr;
};
