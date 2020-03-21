// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRPGGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "OnlineSubsystem.h"
#include "MenuSystem/WidgetBP/MainMenu.h"
#include "MenuSystem/WidgetBP/InGameMenu.h"
#include "MenuSystem/WidgetBP/ServerRow.h"
//#include "OnlineSessionSettings.h"
//#include "Interfaces/OnlineSessionInterface.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"

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

// void UFPSRPGGameInstance::LoadScrollBoxChildWidget()
// {
// 	if (!ensure(ScrollBoxChildClass != nullptr)) return;
// 	ScrollBoxChild = CreateWidget<UScrollBoxChild>(this, ScrollBoxChildClass);
// 
// 	if (!ensure(Menu != nullptr)) return;
// 	if (!ensure(Menu->JoinScrollBox != nullptr)) return;
// 
// 	Menu->JoinScrollBox->AddChild(ScrollBoxChild);
// 	
// 	//to do t shared ref
// }

void UFPSRPGGameInstance::HostSession()
{

	FName SessionName = TEXT("hello hi!");
	IOnlineSubsystem * OnlineSubSystemPtr = IOnlineSubsystem::Get();
	if (OnlineSubSystemPtr != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubSystemPtr %s"), *OnlineSubSystemPtr->GetSubsystemName().ToString());
		SessionInterface = OnlineSubSystemPtr->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			auto ExistingSession = SessionInterface->GetNamedSession(SessionName);
			if (ExistingSession != nullptr)
			{
				SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UFPSRPGGameInstance::OnDestorySessionComplete);
				SessionInterface->DestroySession(SessionName);
			}
			FOnlineSessionSettings SessionSettings;
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UFPSRPGGameInstance::OnHostSessionComplete);
			SessionSettings.bIsLANMatch = true;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.NumPublicConnections = 2;
			SessionInterface->CreateSession(0, SessionName, SessionSettings);
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
	if (bInBool && SessionSearch != NULL && Menu!=nullptr)
	{
		TArray<FString> ServerNames;

		SearchResults.Empty();
		this->SearchResults = SessionSearch->SearchResults;

		UE_LOG(LogTemp, Warning, TEXT("Find session successed"));
		for (FOnlineSessionSearchResult& SessionResult : SessionSearch->SearchResults)
		{

			UE_LOG(LogTemp, Warning, TEXT("Found Session ID: %s"), *SessionResult.GetSessionIdStr());
			ServerNames.Add(*SessionResult.GetSessionIdStr());
		}
		if (!ensure(Menu != nullptr)) return;
		Menu->SetServerList(ServerNames);
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
	if (SelectedIndex.IsSet() && SearchResults.IsValidIndex(SelectedIndex.GetValue()) && SessionInterface.IsValid())
	{
		if (SearchResults[SelectedIndex.GetValue()].IsValid())
		{
			FOnlineSessionSearchResult& SearchResult = SearchResults[SelectedIndex.GetValue()];
			UE_LOG(LogTemp, Warning, TEXT("Has seleted Index, Index is %d"), SelectedIndex.GetValue());
			UE_LOG(LogTemp, Warning, TEXT("Has seleted Index, Name is %s"), *SearchResult.GetSessionIdStr());
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UFPSRPGGameInstance::OnJoinSessionComplete);
			SessionInterface->JoinSession(0, *SearchResult.GetSessionIdStr() , SearchResult);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Do not has seleted Index"));
	}

}

void UFPSRPGGameInstance::OnJoinSessionComplete(FName InName, EOnJoinSessionCompleteResult::Type Result)
{
	//if (Menu != nullptr)
	//{
	//	//Menu->SetServerList({ "Server1","Server2","Server3" });
	//}
	//if (Menu != nullptr)
	//{
	//	Menu->Teardown();
	//}
	if (!SessionInterface.IsValid())
	{
		return;
	}
	FString Adress;
	if (SessionInterface->GetResolvedConnectString(InName, Adress))
	{
		UE_LOG(LogTemp, Warning, TEXT("get adress successs"));
		UEngine* Engine = GetEngine();
		if (!ensure(Engine != nullptr)) return;
		Engine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Adress));

		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (!ensure(PlayerController != nullptr)) return;
		PlayerController->ClientTravel(*Adress, TRAVEL_Absolute, true);
		
		if (!ensure(Menu != nullptr)) return;
		Menu->Teardown();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("get adress Failed"));
	}



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

void UFPSRPGGameInstance::RefreshServerNames()
{
	StartFindSession();
}

void UFPSRPGGameInstance::SetSelectedIndex(uint32 InIndex)
{
	if (!ensure(Menu != nullptr)) return;
	SelectedIndex = InIndex;
	for (UServerRow* Row : Menu->ServerRows)
	{
		if (!ensure(Row != nullptr)) return;
		if (Row->BeSelectedIndex == InIndex)
		{
			Row->SetButtonStyle(false);
		}
		else
		{
			Row->SetButtonStyle(true);
		}
	}
}

void UFPSRPGGameInstance::StartFindSession()
{
	IOnlineSubsystem * OnlineSubSystemPtr = IOnlineSubsystem::Get();
	if (OnlineSubSystemPtr != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubSystemPtr %s"), *OnlineSubSystemPtr->GetSubsystemName().ToString());
		SessionInterface = OnlineSubSystemPtr->GetSessionInterface();

		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		if (SessionSearch.IsValid())
		{
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UFPSRPGGameInstance::OnFindSessionComplete);
			SessionSearch->bIsLanQuery = true;
			SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
			UE_LOG(LogTemp, Warning, TEXT("Start Find a Session"));
		}
		if (!ensure(Menu != nullptr)) return;
		Menu->SetServerList({"Searching Server..."},false);
		SelectedIndex.Reset();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NoOnlineSubSystemPtr"));
	}
}

void UFPSRPGGameInstance::Init()
{
	
	
	
}
