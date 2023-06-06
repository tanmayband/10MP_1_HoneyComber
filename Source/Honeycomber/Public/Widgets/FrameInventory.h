// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utils/Structs.h"
#include "FrameInventory.generated.h"

class UInteractionPopup;
class UIInteractionOption;

DECLARE_DELEGATE_RetVal(bool, FCheckFrameSpaceSignature);
DECLARE_DELEGATE_RetVal_OneParam(bool, FFrameRemoveRequestSignature, uint8 frameIndex);

UCLASS()
class HONEYCOMBER_API UFrameInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupInventory();
	EFrameActionType CurrentAction;
	void AddFrame(FBeeFrameData frameData);
	bool IsInventoryFull();
	FCheckFrameSpaceSignature CheckFrameSpaceDelegate;
	FFrameRemoveRequestSignature OnFrameRemoveRequestDelegate;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UInteractionPopup* FrameList;

	TMap<EFrameActionType, FString> ActionPrefixes = {
		{EFrameActionType::PUT_BACK, "Put back"},
		{EFrameActionType::SCRAPE_DUMP, "Scrape and dump"},
		{EFrameActionType::SCRAPE_INSERT, "Scrape and insert"}
	};

	TArray<FInteractionOptionEnabled> FramesData;

	void RemoveFrame(uint8 frameIndex);
};
