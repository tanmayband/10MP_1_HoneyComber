// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Structs.h"
#include "DialogueManager.generated.h"

class UDataTable;
class AResourceManager;

DECLARE_DELEGATE_TwoParams(FEventGivenSignature, EResourceType givenType, uint8 givenAmount);

UCLASS()
class HONEYCOMBER_API ADialogueManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogueManager();
	void SetupDialogueManager(TMap<EResourceType, uint16> ResourcesData);
	FString StartDialogue(UDataTable* dialogueTable, FName atRowNum);
	FString GetNextDialogue(FName atRowNum);
	TArray<FDialogueOptionEnabled> GetOptions() { return DialogueOptions; };

	void UpdateResourcesState(EResourceType resourceType, uint8 resourceAmount);
	void UpdateEventsState(FString eventName, uint8 eventState);
	TArray<FDialogueOptionEnabled> ProcessOptions();

	FString PickOption(uint8 optionIndex);
	FEventGivenSignature OnEventGivenDelegate;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//UPROPERTY(EditAnywhere)
	UDataTable* DialogueTable;

	TMap<FString, uint8> DialogueEventsState;
	FDialogueDetails CurrentDialogueRow;
	TArray<FDialogueOptionEnabled> DialogueOptions;
	TArray<FDialogueDetails*> DialogueOptionRows;
	TMap<FString, uint8> DialogueEventsExpectedState;
};
