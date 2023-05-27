// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Desk.h"
#include "Widgets/InteractionPopup.h"

void ADesk::UpdateDeskOptions(TArray<FString> newOptions, bool haveEnoughResources)
{
	InteractionPopup->SetupPopupOptions(newOptions);
	InteractionPopup->ToggleOptionEnabled(0, haveEnoughResources);
}

void ADesk::ClearDeskOptions()
{
	InteractionPopup->ClearOptions();
}

void ADesk::InteractOption(int32 index)
{
	OnVisitorResponseDelegate.ExecuteIfBound(index);
}