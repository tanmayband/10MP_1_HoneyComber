// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionOption.generated.h"

class UTextBlock;
class UImage;

DECLARE_DELEGATE_OneParam(FOnOptionSelectedSignature, uint8 SelectedOptionIndex)

UCLASS()
class HONEYCOMBER_API UInteractionOption : public UUserWidget
{
	GENERATED_BODY()

public:
	void PreConstruct(bool IsDesignTime);

	void SetupOption(FString option, uint8 optionIndex);
	void ToggleHighlightOption(bool highlighted);
	void ToggleClickableOption(bool clickable);

	void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	FOnOptionSelectedSignature OnOptionSelectedDelegate;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UImage* OptionBG;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* OptionName;
	uint8 OptionIndex;
	bool isClickable = true;
};
