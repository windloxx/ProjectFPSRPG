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
	UMainMenu(const FObjectInitializer & ObjectInitializer);
	void SetMenuInterface(IMenuInterface* InMenuInterface);

	void Setup();
	void Teardown();

	UFUNCTION()
	void MenuRefreshServerList();

	void SetServerList(TArray<FString> ServerNames,bool ClickAble = true);
	
	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerScrollBox;

	//class UScrollBoxChild* JoinScrollBoxChild;
	TSubclassOf<class UUserWidget> ServerRowClass;
		
protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void HostServer();
	UFUNCTION()
	void OpenJoinMenu();
	UFUNCTION()
	void OpenMainMenu();
	UFUNCTION()
	void OpenQuitMenu();
	UFUNCTION()
	void ConfirmJoin();
	UFUNCTION()
	void MainMenuQuitGame();

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
	class UButton* MenuConfirmQuitButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* MenuCancelQuitEnsureButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* MenuQuitGameButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* RefreshServerListButton;
	

	

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;
	UPROPERTY(meta = (BindWidget))
	class UWidget* QuitEnsureMenu;
	
	IMenuInterface* MenuInterfacePtr;
};
