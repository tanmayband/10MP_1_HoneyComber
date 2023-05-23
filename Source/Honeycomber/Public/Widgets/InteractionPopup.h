// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionPopup.generated.h"

class UTextBlock;
class UVerticalBox;
class UInteractionOption;

DECLARE_DELEGATE_OneParam(FOnOptionSelectedSignature, int32 SelectedOptionIndex)

UCLASS()
class HONEYCOMBER_API UInteractionPopup : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupPopup(FString PopupName, TArray<FString> PopupOptions);
	void HighlightInteractionOption(int32 optionIndex);
	void UnhighlightAllInteractionOptions();

	FOnOptionSelectedSignature OnOptionSelectedDelegate;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* InteractableName;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UVerticalBox* OptionsBox;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UInteractionOption> InteractionOptionClass;
	TArray<UInteractionOption*> AllOptions;

	void ClearOptions();
	UFUNCTION()
		void InteractionOptionSelected(int32 optionIndex);
};
