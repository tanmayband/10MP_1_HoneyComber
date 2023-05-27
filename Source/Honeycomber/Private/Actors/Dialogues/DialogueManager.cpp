// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Dialogues/DialogueManager.h"
#include "Actors/ResourceManager.h"
#include "Utils/Structs.h"
#include "Utils/Enums.h"

// Sets default values
ADialogueManager::ADialogueManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FString ADialogueManager::StartDialogue(UDataTable* dialogueTable, FName atRowNum)
{
	DialogueTable = dialogueTable;
	FDialogueDetails* tableRow = DialogueTable->FindRow<FDialogueDetails>(atRowNum, "");
	TArray<FName> nextDialogueRows = tableRow->NextDialogues;
	DialogueOptions.Empty();

	switch (tableRow->DialogueType)
	{
		case EDialogueType::ASK:
		{
			if (tableRow->DialogueEvent == "EventHoney")
			{
				uint8 honeyAmount = FMath::RandRange(1, 5);
				
				// in dialogue, replace "{x}" with honeyAmount

				for (FName nextDialogueRowName : nextDialogueRows)
				{
					FDialogueDetails* nextDialogueRow = DialogueTable->FindRow<FDialogueDetails>(nextDialogueRowName, "");
					DialogueOptions.Add(nextDialogueRow->DialogueText);
					if (nextDialogueRow->DialogueType == EDialogueType::GIVE && tableRow->DialogueEvent == "EventHoney")
					{
						bool dialogueAvailable = honeyAmount <= DialogueEventsState["EventHoney"];

						// use dialogueAvailable to visually disable/enable option
						UE_LOG(LogTemp, Warning, TEXT("Dialogue %s is available: %d"), *nextDialogueRow->DialogueText, dialogueAvailable);
					}
				}

			}
			break;
		}
	}
	return tableRow->DialogueText;
}

TArray<FString> ADialogueManager::GetOptions()
{
	return DialogueOptions;
}

// Called when the game starts or when spawned
void ADialogueManager::BeginPlay()
{
	Super::BeginPlay();

	DialogueEventsState.Add("EventHoney", 10);
}

