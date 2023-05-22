// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionPopup.generated.h"

class UTextBlock;

UCLASS()
class HONEYCOMBER_API UInteractionPopup : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupPopup(FString PopupName);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* InteractableName;
};
