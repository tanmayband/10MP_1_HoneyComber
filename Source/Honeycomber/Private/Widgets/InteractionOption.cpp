// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractionOption.h"
#include "Components/TextBlock.h"

void UInteractionOption::PreConstruct(bool IsDesignTime)
{
	//SetVisibility(ESlateVisibility::Visible);
}

void UInteractionOption::SetupOption(FString option)
{
	OptionName->SetText(FText::FromString(option));
	ToggleSelectOption(false);
}

void UInteractionOption::ToggleSelectOption(bool selected)
{
	OptionBG->SetVisibility(selected ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
}

void UInteractionOption::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ToggleSelectOption(true);
}

void UInteractionOption::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	ToggleSelectOption(false);
}

FReply UInteractionOption::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FEventReply().NativeReply;
}
