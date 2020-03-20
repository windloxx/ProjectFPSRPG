// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/WidgetBP/MenuInterface.h"
#include "FPSRPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFPSRPG_API UFPSRPGGameInstance : public UGameInstance,public IMenuInterface
{
	GENERATED_BODY()

public:
	UFPSRPGGameInstance(const FObjectInitializer & ObjectInitializer);

	//FText SessionName; ;

	//UI function
	UFUNCTION(Exec,BlueprintCallable)
	void LoadMenuWidget();
	UFUNCTION(Exec,BlueprintCallable)
	void LoadInGameMenuWidget();
// 	UFUNCTION(Exec,BlueprintCallable)
// 	void LoadScrollBoxChildWidget();
	//Network function
	/**
*	Function to host a game!
*
*	@Param		UserID			User that started the request
*	@Param		SessionName		Name of the Session
*	@Param		bIsLAN			Is this is LAN Game?
*	@Param		bIsPresence		"Is the Session to create a presence Session"
*	@Param		MaxNumPlayers	        Number of Maximum allowed players on this "Session" (Server)
*/
	UFUNCTION(Exec)
	void HostSession() override;
	UFUNCTION()
	void OnHostSessionComplete(FName InName, bool bInBool);
	UFUNCTION()
	void OnDestorySessionComplete(FName InName, bool bInBool);
	UFUNCTION()
	void OnFindSessionComplete(bool bInBool);
	//

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Adress) override;

	UFUNCTION(Exec)
	void BackToMainMenu() override;

	UFUNCTION(Exec)
	void QuitTheGame() override;

	UFUNCTION(Exec)
	void RefreshServerNames() override;
	
	void SetSelectedIndex(uint32 InIndex);

	void StartFindSession();

	TSharedPtr <class FOnlineSessionSearch> SessionSearch;
private:

	TOptional <uint32> SelectedIndex;

	virtual void Init();

	TSubclassOf<class UUserWidget>MainMenuClass;
	TSubclassOf<class UUserWidget>InGameMenuClass;
	/*TSubclassOf<class UUserWidget>ScrollBoxChildClass;*/

	class UMainMenu* Menu;
	class UInGameMenu* InGameMenu;
	//class UScrollBoxChild* ScrollBoxChild;


//public:
//
//	virtual void Init() override;

};
