// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/Interactable.h"
#include "Desk.generated.h"

DECLARE_DELEGATE_OneParam(FVisitorResponseSignature, int32 responseIndex);

UCLASS()
class HONEYCOMBER_API ADesk : public AInteractable
{
	GENERATED_BODY()

public:
	FVisitorResponseSignature OnVisitorResponseDelegate;
	void UpdateDeskOptions(TArray<FString> newOptions, bool haveEnoughResources);
	void ClearDeskOptions();

private:
	void InteractOption(int32 index) override;
};
