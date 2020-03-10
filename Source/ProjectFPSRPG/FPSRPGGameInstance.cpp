// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRPGGameInstance.h"

#include "Engine/Engine.h"

//void UFPSRPGGameInstance::Init()
//{
//	UE_LOG(LogTemp, Warning, TEXT("GameInstanceIni"));
//}

UFPSRPGGameInstance::UFPSRPGGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstanceIni"));
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