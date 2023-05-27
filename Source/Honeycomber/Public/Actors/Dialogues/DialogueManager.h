// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogueManager.generated.h"

class UDataTable;
class AResourceManager;

UCLASS()
class HONEYCOMBER_API ADialogueManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogueManager();
	FString StartDialogue(UDataTable* dialogueTable, FName atRowNum);
	TArray<FString> GetOptions();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//UPROPERTY(EditAnywhere)
		UDataTable* DialogueTable;

	AResourceManager* ResourceManager;
	TMap<FString, uint8> DialogueEventsState;
	TArray<FString> DialogueOptions;

};
