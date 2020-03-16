// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRPGGameInstance.h"

#include "Engine/Engine.h"
#include "OnlineSubsystem.h"
#include "MenuSystem/WidgetBP/MainMenu.h"
#include "MenuSystem/WidgetBP/InGameMenu.h"

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

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/UI/MenuSystem/WidgetBP/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
	InGameMenuClass = InGameMenuBPClass.Class;

	//UE_LOG(LogTemp, Warning, TEXT("MainMenuClass %s"),*MainMenuClass->GetName());
}

void UFPSRPGGameInstance::LoadMenuWidget()
{
	if (!ensure(MainMenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MainMenuClass);

	if (!ensure(Menu != nullptr)) return;
	Menu->Setup();
	Menu->SetMenuInterface(this);
}



void UFPSRPGGameInstance::LoadInGameMenuWidget()
{
	if (!ensure(InGameMenuClass != nullptr)) return;
	InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);

	if (!ensure(InGameMenu != nullptr)) return;
	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

// void UFPSRPGGameInstance::CancelInGameMenuWidget()
// {
// 	if (InGameMenu != nullptr)
// 	{
// 		InGameMenu->CancelInGameMenu();
// 	}
// }

/////https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
void UFPSRPGGameInstance::Host()
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hosting Server"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UFPSRPGGameInstance::Join(const FString& Adress)
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Joining %s"),*Adress));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(*Adress, TRAVEL_Absolute,true);
}

void UFPSRPGGameInstance::BackToMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel("/Game/Maps/MainMenu/MainMenu", TRAVEL_Absolute, true);
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
