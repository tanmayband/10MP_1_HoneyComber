// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utils/Structs.h"
#include "InteractionPopup.generated.h"

class UCanvasPanel;
class UTextBlock;
class UVerticalBox;
class UInteractionOption;

DECLARE_DELEGATE_OneParam(FOnOptionSelectedSignature, uint8 SelectedOptionIndex)

UCLASS()
class HONEYCOMBER_API UInteractionPopup : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupPopup(FString PopupName, TArray<FInteractionOptionEnabled> PopupOptions, FVector2D PopupPivot);
	void SetupPopupName(FString PopupName);
	void SetupPopupOptions(TArray<FInteractionOptionEnabled> PopupOptions);
	void ClearOptions();
	void HighlightInteractionOption(uint8 optionIndex);
	void UnhighlightAllInteractionOptions();
	void ToggleOptionEnabled(uint8 optionIndex, bool enabled);

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

	UFUNCTION()
		void InteractionOptionSelected(uint8 optionIndex);
};
