// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Desk.h"
#include "Widgets/InteractionPopup.h"

void ADesk::UpdateDeskOptions(TArray<FInteractionOptionEnabled> newOptions)
{
	InteractionPopup->SetupPopupOptions(newOptions);
}

void ADesk::ClearDeskOptions()
{
	InteractionPopup->ClearOptions();
}

void ADesk::InteractOption(uint8 index)
{
	OnVisitorResponseDelegate.ExecuteIfBound(index);
}