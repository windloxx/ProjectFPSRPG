// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFPSRPG_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* InMenuInterface);

	void Setup();
	void Teardown();
	
		
protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void HostServer();
	UFUNCTION()
	void OpenJoinMenu();
	UFUNCTION()
	void OpenMainMenu();
	UFUNCTION()
	void ConfirmJoin();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinCancelButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenuJoinButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* JoinIPAdressField;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;
	
	IMenuInterface* MenuInterfacePtr;
};
