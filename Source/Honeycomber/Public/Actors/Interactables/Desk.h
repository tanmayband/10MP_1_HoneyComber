// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/Interactable.h"
#include "Utils/Structs.h"
#include "Desk.generated.h"

DECLARE_DELEGATE_OneParam(FVisitorResponseSignature, uint8 responseIndex);

UCLASS()
class HONEYCOMBER_API ADesk : public AInteractable
{
	GENERATED_BODY()

public:
	FVisitorResponseSignature OnVisitorResponseDelegate;
	void UpdateDeskOptions(TArray<FInteractionOptionEnabled> newOptions);
	void ClearDeskOptions();

private:
	void InteractOption(uint8 index) override;
};
