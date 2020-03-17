// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}
	
	if (!ensure(InGameMenuCancelButton != nullptr)) return false;
	InGameMenuCancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelInGameMenu);
	if (!ensure(InGameBackToMainMenuButton != nullptr)) return false;
	InGameBackToMainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::OpenInGameBackToMainMenuEnsure);
	if (!ensure(InGameBackToMainMenuEnsureButton != nullptr)) return false;
	InGameBackToMainMenuEnsureButton->OnClicked.AddDynamic(this, &UInGameMenu::OpenMainMenu);
	if (!ensure(InGameBackToMainMenuCancelButton != nullptr)) return false;
	InGameBackToMainMenuCancelButton->OnClicked.AddDynamic(this, &UInGameMenu::OpenInGameMenu);

	return true;
}

void UInGameMenu::CancelInGameMenu()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();

	FInputModeGameOnly GameInputMode;

	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->SetInputMode(GameInputMode);
	PlayerController->bShowMouseCursor = false;

	this->RemoveFromViewport();
}

void UInGameMenu::OpenMainMenu()
{
	if (MenuInterfacePtr != nullptr)
	{
		CancelInGameMenu();
		MenuInterfacePtr->BackToMainMenu();
	}
}

void UInGameMenu::OpenInGameMenu()
{
	if (!ensure(InGameMenuSwitcher != nullptr)) return;
	if (!ensure(InGameMenuOverLay != nullptr)) return;
	InGameMenuSwitcher->SetActiveWidget(InGameMenuOverLay);
}

void UInGameMenu::OpenInGameBackToMainMenuEnsure()
{
	if (!ensure(InGameMenuSwitcher != nullptr)) return;
	if (!ensure(InGameBackToMainMenuEnsure != nullptr)) return;
	InGameMenuSwitcher->SetActiveWidget(InGameBackToMainMenuEnsure);
}

void UInGameMenu::SetMenuInterface(IMenuInterface* InMenuInterface)
{
	MenuInterfacePtr = InMenuInterface;
}

void UInGameMenu::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();

	FInputModeUIOnly MenuInputMode;
	MenuInputMode.SetWidgetToFocus(this->TakeWidget());
	MenuInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);

	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->SetInputMode(MenuInputMode);
	PlayerController->bShowMouseCursor = true;

	if (InGameMenuActiveSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), InGameMenuActiveSound);
	}
	
}
