// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionPopup.generated.h"

class UTextBlock;
class UVerticalBox;
class UInteractionOption;

UCLASS()
class HONEYCOMBER_API UInteractionPopup : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupPopup(FString PopupName, TArray<FString> PopupOptions);
	void SelectInteractionOption(int32 optionIndex);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* InteractableName;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UVerticalBox* OptionsBox;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UInteractionOption> InteractionOptionClass;
	TArray<UInteractionOption*> AllOptions;

	void ClearOptions();
};
