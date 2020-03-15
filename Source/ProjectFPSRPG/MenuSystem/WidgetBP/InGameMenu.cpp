// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"

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
}
