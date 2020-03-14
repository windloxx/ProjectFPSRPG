// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRPGGameInstance.h"

#include "Engine/Engine.h"
#include "OnlineSubsystem.h"

#include "Blueprint/UserWidget.h"

//void UFPSRPGGameInstance::Init()
//{
//	UE_LOG(LogTemp, Warning, TEXT("GameInstanceIni"));
//}

UFPSRPGGameInstance::UFPSRPGGameInstance(const FObjectInitializer & ObjectInitializer)
{

	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/UI/MenuSystem/WidgetBP/WBP_MainMenu"));
	if (!ensure(MainMenuBPClass.Class != nullptr)) return;

	MainMenuClass = MainMenuBPClass.Class;

	UE_LOG(LogTemp, Warning, TEXT("MainMenuClass %s"),*MainMenuClass->GetName());
}

void UFPSRPGGameInstance::LoadMenuWidget()
{
	if (!ensure(MainMenuClass != nullptr)) return;
	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MainMenuClass);

	if (!ensure(Menu != nullptr)) return;
	Menu->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	
	FInputModeUIOnly MenuInputMode;
	MenuInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	MenuInputMode.SetWidgetToFocus(Menu->TakeWidget());

	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->SetInputMode(MenuInputMode);
	PlayerController->bShowMouseCursor = true;
}

void UFPSRPGGameInstance::Host()
{
/////https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hosting Server"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UFPSRPGGameInstance::Join(const FString& Adress)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Joining %s"),*Adress));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(*Adress, TRAVEL_Absolute,true);
}

void UFPSRPGGameInstance::Init()
{
	IOnlineSubsystem * OnlineSubSystemPtr = IOnlineSubsystem::Get();
	if (OnlineSubSystemPtr != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubSystemPtr %s"), *OnlineSubSystemPtr->GetSubsystemName().ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NoOnlineSubSystemPtr"));
	}
	
}
