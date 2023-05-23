// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractionOption.h"
#include "Components/TextBlock.h"

void UInteractionOption::PreConstruct(bool IsDesignTime)
{
	//SetVisibility(ESlateVisibility::Visible);
}

void UInteractionOption::SetupOption(FString option, int32 optionIndex)
{
	OptionIndex = optionIndex;
	OptionName->SetText(FText::FromString(option));
	ToggleHighlightOption(false);
}

void UInteractionOption::ToggleHighlightOption(bool selected)
{
	OptionBG->SetVisibility(selected ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
}

void UInteractionOption::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ToggleHighlightOption(true);
}

void UInteractionOption::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	ToggleHighlightOption(false);
}

FReply UInteractionOption::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	OnOptionSelectedDelegate.ExecuteIfBound(OptionIndex);
	return FEventReply().NativeReply;
}
