// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractionOption.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UInteractionOption::PreConstruct(bool IsDesignTime)
{
	//SetVisibility(ESlateVisibility::Visible);
}

void UInteractionOption::SetupOption(FString option, uint8 optionIndex)
{
	OptionIndex = optionIndex;
	OptionName->SetText(FText::FromString(option));
	ToggleHighlightOption(false);
	ToggleClickableOption(true);
}

void UInteractionOption::ToggleHighlightOption(bool selected)
{
	OptionBG->SetVisibility(selected ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
}

void UInteractionOption::ToggleClickableOption(bool clickable)
{
	isClickable = clickable;
	FLinearColor TextColour = isClickable ? FLinearColor(1,1,1,1) : FLinearColor(0.5f, 0.5f, 0.5f, 0.5f);
	OptionName->SetColorAndOpacity(TextColour);
	if (!isClickable)
	{
		ToggleHighlightOption(false);
	}
}

void UInteractionOption::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(isClickable)
		ToggleHighlightOption(true);
}

void UInteractionOption::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	ToggleHighlightOption(false);
}

FReply UInteractionOption::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (isClickable)
	{
		OnOptionSelectedDelegate.ExecuteIfBound(OptionIndex);
	}
	return FEventReply().NativeReply;
}
