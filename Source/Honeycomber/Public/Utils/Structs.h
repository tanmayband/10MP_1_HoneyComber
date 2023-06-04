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
struct FInteractionOptionEnabled
{
	GENERATED_BODY()

	FInteractionOptionEnabled() {};
	FInteractionOptionEnabled(FString optionText, bool optionEnabled) : OptionText(optionText), OptionEnabled(optionEnabled) {};
	UPROPERTY(EditAnywhere)
		FString OptionText;
	UPROPERTY(EditAnywhere)
		bool OptionEnabled = true;
};

USTRUCT(BlueprintType)
struct FVisitorData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
		FString VisitorName;
	UPROPERTY(EditAnywhere)
		EVisitorType VisitorType;
	UPROPERTY(EditAnywhere)
		UDataTable* VisitorDialogueTable;
};

USTRUCT()
struct FBeeFrameData
{
	GENERATED_BODY()

	UPROPERTY()
		float HoneyFill;
};