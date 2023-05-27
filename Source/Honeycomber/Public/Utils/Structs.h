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
		int32 ProductAmount;
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
		int8 DialogueEventValue;
};