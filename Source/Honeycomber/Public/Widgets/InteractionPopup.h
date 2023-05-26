// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionPopup.generated.h"

class UCanvasPanel;
class UTextBlock;
class UVerticalBox;
class UInteractionOption;

DECLARE_DELEGATE_OneParam(FOnOptionSelectedSignature, int32 SelectedOptionIndex)

UCLASS()
class HONEYCOMBER_API UInteractionPopup : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupPopup(FString PopupName, TArray<FString> PopupOptions, FVector2D PopupPivot);
	void SetupPopupName(FString PopupName);
	void HighlightInteractionOption(int32 optionIndex);
	void UnhighlightAllInteractionOptions();
	void ToggleOptionEnabled(int32 optionIndex, bool enabled);

	FOnOptionSelectedSignature OnOptionSelectedDelegate;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UCanvasPanel* Container;
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
