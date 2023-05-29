#pragma once
#include "Enums.h"
#include "Engine/DataTable.h"
#include "Structs.generated.h"

USTRUCT()
struct FExchangeProduct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		EResourceType ProductType;
	UPROPERTY(EditAnywhere)
		uint8 ProductAmount;
};

USTRUCT()
struct FDialogueDetails : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		EDialogueType DialogueType;
	UPROPERTY(EditAnywhere)
		FString DialogueEvent;
	UPROPERTY(EditAnywhere)
		FString DialogueText;
	UPROPERTY(EditAnywhere)
		TArray<FName> NextDialogues;
	UPROPERTY(EditAnywhere)
		uint8 DialogueEventValue;
};

USTRUCT()
struct FDialogueOptionEnabled
{
	GENERATED_BODY()

	FDialogueOptionEnabled() {};
	FDialogueOptionEnabled(FString dialogueText, bool dialogueEnabled) : DialogueText(dialogueText), DialogueEnabled(dialogueEnabled) {};
	UPROPERTY(EditAnywhere)
		FString DialogueText;
	UPROPERTY(EditAnywhere)
		bool DialogueEnabled;
};