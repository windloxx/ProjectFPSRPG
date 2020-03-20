// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuInterface.h"
#include "ServerRow.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTFPSRPG_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
public:
	UServerRow(const FObjectInitializer & ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;
	UPROPERTY(meta = (BindWidget))
	class UButton* ServerSelectButton;


	UFUNCTION()
	void OnServerButtonClicked();
	
	uint32 BeSelectedIndex;

	void SetBeSelectedIndex(uint32 InIndex);
	void SetMenuInterFace(IMenuInterface* InMenuInterface);
	IMenuInterface* MenuInterfacePtr;
};
