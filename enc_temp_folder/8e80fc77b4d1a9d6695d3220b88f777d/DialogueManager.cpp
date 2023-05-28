// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Dialogues/DialogueManager.h"
#include "Utils/Structs.h"
#include "Utils/Utils.h"

// Sets default values
ADialogueManager::ADialogueManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ADialogueManager::SetupDialogueManager(TMap<EResourceType, uint8> ResourcesData)
{
	for (const TPair<EResourceType, uint8>& pair : ResourcesData)
	{
		DialogueEventsState.Add(EnumUtils::ResourceToEventName[pair.Key], pair.Value);
	}
}

FString ADialogueManager::StartDialogue(UDataTable* dialogueTable, FName atRowNum)
{
	DialogueTable = dialogueTable;
	CurrentDialogueRow = DialogueTable->FindRow<FDialogueDetails>(atRowNum, "");
	TArray<FName> nextDialogueRows = CurrentDialogueRow->NextDialogues;
	DialogueOptionRows.Empty();

	switch (CurrentDialogueRow->DialogueType)
	{
		case EDialogueType::ASK:
		{
			FString currentDialogueEvent = CurrentDialogueRow->DialogueEvent;

			// If currentDialogueEvent does not exist in TMap, insert it to process a potential upcoming dialogue
			// Eg. something like, "SUS_EVENT_1"
			if (!DialogueEventsState.Contains(currentDialogueEvent))
			{
				DialogueEventsState.Add(currentDialogueEvent, 1);
			}

			// special handling for parameterized dialogues
			if (CurrentDialogueRow->DialogueText.Contains("{x}"))
			{
				// needs random amount
				uint8 eventAmount = FMath::RandRange(1, 5);
				// insert this back into the current dialogue row (temporarily)
				CurrentDialogueRow->DialogueText = CurrentDialogueRow->DialogueText.Replace(TEXT("{x}"), *FString::FromInt(eventAmount));
				CurrentDialogueRow->DialogueEventValue = eventAmount;
			}

			// parse next dialogue options, and check for disabling
			for (FName nextDialogueRowName : nextDialogueRows)
			{
				FDialogueDetails* nextDialogueRow = DialogueTable->FindRow<FDialogueDetails>(nextDialogueRowName, "");
				
				DialogueOptionRows.Add(nextDialogueRow);
			}
			ProcessOptions();
			break;
		}
	}
	return CurrentDialogueRow->DialogueText;
}

void ADialogueManager::UpdateResourcesState(EResourceType resourceType, uint8 resourceAmount)
{
	UpdateEventsState(EnumUtils::ResourceToEventName[resourceType], resourceAmount);
}

void ADialogueManager::UpdateEventsState(FString eventName, uint8 eventState)
{
	DialogueEventsState[eventName] = eventState;
	ProcessOptions();
}

// Called when the game starts or when spawned
void ADialogueManager::BeginPlay()
{
	Super::BeginPlay();
}

TArray<FDialogueOptionEnabled> ADialogueManager::ProcessOptions()
{
	DialogueOptions.Empty();
	for (FDialogueDetails* dialogueOptionRow : DialogueOptionRows)
	{
		if (dialogueOptionRow->DialogueType == EDialogueType::GIVE && dialogueOptionRow->DialogueEvent == CurrentDialogueRow->DialogueEvent)
		{
			bool dialogueAvailable = CurrentDialogueRow->DialogueEventValue <= DialogueEventsState[CurrentDialogueRow->DialogueEvent];
			
			DialogueOptions.Add(FDialogueOptionEnabled(dialogueOptionRow->DialogueText, dialogueAvailable));
		}
		else
		{
			DialogueOptions.Add(FDialogueOptionEnabled(dialogueOptionRow->DialogueText, true));
		}
	}
	return DialogueOptions;
}

FString ADialogueManager::PickOption(uint8 optionIndex)
{
	FDialogueDetails* pickedOptionRow = DialogueOptionRows[optionIndex];
	switch (pickedOptionRow->DialogueType)
	{
		case EDialogueType::GIVE:
		{
			// find out what was given and how much
			FString giveEvent = CurrentDialogueRow->DialogueEvent;
			EResourceType givenResource;
			const EResourceType* givenResourcePtr = EnumUtils::EventToResourceName(giveEvent);
			if (givenResourcePtr == nullptr)
				givenResource = EResourceType::NONE;	// maybe use ITEM for random items?
			else
				givenResource = *givenResourcePtr;
			uint8 givenAmount = CurrentDialogueRow->DialogueEventValue;

			// pass this intel to visitor manager, to give to resource manager
			OnEventGivenDelegate.ExecuteIfBound(givenResource, givenAmount);
			break;
		}
	}

	return FString();
}

