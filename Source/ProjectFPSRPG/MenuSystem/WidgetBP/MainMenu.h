// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFPSRPG_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

		
protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void HostServer();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;
	
};
