// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRPGGameInstance.h"

#include "Engine/Engine.h"
#include "OnlineSubsystem.h"
#include "MenuSystem/WidgetBP/MainMenu.h"
#include "MenuSystem/WidgetBP/InGameMenu.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

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

void UFPSRPGGameInstance::HostSession()
{

	FName SessionName = TEXT("hello hi!");
	IOnlineSubsystem * OnlineSubSystemPtr = IOnlineSubsystem::Get();
	if (OnlineSubSystemPtr != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubSystemPtr %s"), *OnlineSubSystemPtr->GetSubsystemName().ToString());
		IOnlineSessionPtr SessionInterface = OnlineSubSystemPtr->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			auto ExistingSession = SessionInterface->GetNamedSession(SessionName);
			if (ExistingSession == nullptr)
			{
				FOnlineSessionSettings SessionSettings;
				SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UFPSRPGGameInstance::OnHostSessionComplete);
				SessionSettings.bIsLANMatch = true;
				SessionSettings.bShouldAdvertise = true;
				SessionSettings.NumPublicConnections = 2;
				SessionInterface->CreateSession(0, SessionName, SessionSettings);
			}
			else
			{
				SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UFPSRPGGameInstance::OnDestorySessionComplete);
				SessionInterface->DestroySession(SessionName);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NoOnlineSubSystemPtr"));
	}
}

void UFPSRPGGameInstance::OnHostSessionComplete(FName InName, bool bInBool)
{
	if (bInBool)
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
		UE_LOG(LogTemp, Warning, TEXT("Host Session Successed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Host Session Failed"));
	}
	
}

void UFPSRPGGameInstance::OnDestorySessionComplete(FName InName, bool bInBool)
{
	if (bInBool)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destory session successed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Destory session Failed"));
	}
	
}

void UFPSRPGGameInstance::OnFindSessionComplete(bool bInBool)
{
	if (bInBool && SessionSearch != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Find session successed"));
		for (FOnlineSessionSearchResult& SessionResult : SessionSearch->SearchResults)
		{

			UE_LOG(LogTemp, Warning, TEXT("Found Session ID: %s"), *SessionResult.GetSessionIdStr());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Find session failed"));
	}
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

void UFPSRPGGameInstance::QuitTheGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ConsoleCommand("quit");
}

void UFPSRPGGameInstance::Init()
{
	IOnlineSubsystem * OnlineSubSystemPtr = IOnlineSubsystem::Get();
	if (OnlineSubSystemPtr != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubSystemPtr %s"), *OnlineSubSystemPtr->GetSubsystemName().ToString());
		IOnlineSessionPtr SessionInterface = OnlineSubSystemPtr->GetSessionInterface();

		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		if (SessionSearch.IsValid())
		{
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UFPSRPGGameInstance::OnFindSessionComplete);
			SessionSearch->bIsLanQuery = true;
			SessionInterface->FindSessions(0,SessionSearch.ToSharedRef());
			UE_LOG(LogTemp, Warning, TEXT("Start Find a Session"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NoOnlineSubSystemPtr"));
	}
	
}
