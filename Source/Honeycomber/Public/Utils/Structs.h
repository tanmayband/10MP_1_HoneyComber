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
struct FVisitorDialogue : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		FString DialogueText;
	UPROPERTY(EditAnywhere)
		EVisitorDialogue DialogueType;
	UPROPERTY(EditAnywhere)
		FExchangeProduct DialogueData;
	UPROPERTY(EditAnywhere)
		TArray<FName> NextDialogues;
};