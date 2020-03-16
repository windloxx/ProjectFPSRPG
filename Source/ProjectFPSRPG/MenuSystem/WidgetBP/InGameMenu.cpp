// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"

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
	InGameBackToMainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::OpenMainMenu);

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
