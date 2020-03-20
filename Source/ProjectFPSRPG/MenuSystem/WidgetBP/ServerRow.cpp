// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

UServerRow::UServerRow(const FObjectInitializer & ObjectInitializer) :Super(ObjectInitializer)
{
	
}

void UServerRow::SetMenuInterFace(IMenuInterface* InMenuInterface)
{
	if (!ensure(InMenuInterface != nullptr)) return;
	MenuInterfacePtr = InMenuInterface;
}

void UServerRow::OnServerButtonClicked()
{
	MenuInterfacePtr->SetSelectedIndex(BeSelectedIndex);
}

void UServerRow::SetBeSelectedIndex(uint32 InIndex)
{
	if (!ensure(ServerSelectButton != nullptr)) return;
	ServerSelectButton->OnClicked.AddDynamic(this, &UServerRow::OnServerButtonClicked);
	BeSelectedIndex = InIndex;
}


