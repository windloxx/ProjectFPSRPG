// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/WidgetBP/MenuInterface.h"
#include "FPSRPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFPSRPG_API UFPSRPGGameInstance : public UGameInstance,public IMenuInterface
{
	GENERATED_BODY()

public:
	UFPSRPGGameInstance(const FObjectInitializer & ObjectInitializer);

	UFUNCTION(Exec,BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(Exec,BlueprintCallable)
	void LoadInGameMenuWidget();

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Adress) override;

	UFUNCTION(Exec)
	void BackToMainMenu() override;

	UFUNCTION(Exec)
	void QuitTheGame() override;

private:

	virtual void Init();

	TSubclassOf<class UUserWidget>MainMenuClass;
	TSubclassOf<class UUserWidget>InGameMenuClass;

	class UMainMenu* Menu;
	class UInGameMenu* InGameMenu;


//public:
//
//	virtual void Init() override;

};
