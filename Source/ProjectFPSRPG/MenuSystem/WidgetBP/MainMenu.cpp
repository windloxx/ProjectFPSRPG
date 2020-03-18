// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	if (!ensure(JoinMenuJoinButton != nullptr)) return false;
	JoinMenuJoinButton->OnClicked.AddDynamic(this, &UMainMenu::ConfirmJoin);
	if (!ensure(JoinCancelButton != nullptr)) return false;
	JoinCancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	if (!ensure(MenuConfirmQuitButton != nullptr)) return false;
	MenuConfirmQuitButton->OnClicked.AddDynamic(this, &UMainMenu::MainMenuQuitGame);
	if (!ensure(MenuCancelQuitEnsureButton != nullptr)) return false;
	MenuCancelQuitEnsureButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	if (!ensure(MenuQuitGameButton != nullptr)) return false;
	MenuQuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::OpenQuitMenu);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* InMenuInterface)
{
	MenuInterfacePtr = InMenuInterface;
}

void UMainMenu::Setup()
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

void UMainMenu::Teardown()
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

void UMainMenu::ConfirmJoin()
{
	UE_LOG(LogTemp, Warning, TEXT("Im gonna to Join server!"));
	if (MenuInterfacePtr != nullptr)
	{
		if (!ensure(JoinIPAdressField != nullptr)) return;
		const FString& IPAdress = JoinIPAdressField->GetText().ToString();
		UE_LOG(LogTemp, Warning, TEXT("IP adress input is %s"), *IPAdress);
		MenuInterfacePtr->Join(IPAdress);
	}
}

void UMainMenu::MainMenuQuitGame()
{
	if (MenuInterfacePtr != nullptr)
	{
		MenuInterfacePtr->QuitTheGame();
	}
}

void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Im gonna to host server!"));
	if (MenuInterfacePtr != nullptr)
	{
		MenuInterfacePtr->HostSession();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::OpenQuitMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(QuitEnsureMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(QuitEnsureMenu);
}
