// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Desk.h"
#include "Widgets/InteractionPopup.h"

void ADesk::UpdateDeskOptions(TArray<FDialogueOptionEnabled> newOptions)
{
	TArray<FString> newOptionStrings;
	TArray<bool> newOptionEnableds;
	for (FDialogueOptionEnabled option : newOptions)
	{
		newOptionStrings.Add(option.DialogueText);
		newOptionEnableds.Add(option.DialogueEnabled);
	}
	InteractionPopup->SetupPopupOptions(newOptionStrings, newOptionEnableds);
}

void ADesk::ClearDeskOptions()
{
	InteractionPopup->ClearOptions();
}

void ADesk::InteractOption(int32 index)
{
	OnVisitorResponseDelegate.ExecuteIfBound(index);
}