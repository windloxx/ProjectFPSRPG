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

	//Button events
	UFUNCTION()
	void CancelInGameMenu();
	UFUNCTION()
	void OpenMainMenu();
	UFUNCTION()
	void OpenInGameMenu();
	UFUNCTION()
	void OpenInGameBackToMainMenuEnsure();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* InGameMenuActiveSound;

protected:
	virtual bool Initialize() override;


private:
	IMenuInterface* MenuInterfacePtr;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* InGameMenuSwitcher;

	//Switcher Sub Layers//
	UPROPERTY(meta = (BindWidget))
	class UWidget* InGameMenuOverLay;
	UPROPERTY(meta = (BindWidget))
	class UWidget* InGameBackToMainMenuEnsure;

	//Bind Buttons//
	UPROPERTY(meta = (BindWidget))
	class UButton* InGameMenuCancelButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* InGameBackToMainMenuButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* InGameBackToMainMenuEnsureButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* InGameBackToMainMenuCancelButton;

};
