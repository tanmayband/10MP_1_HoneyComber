// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractionOption.h"
#include "Components/TextBlock.h"

void UInteractionOption::SetupOption(FString option)
{
	OptionName->SetText(FText::FromString(option));
}

void UInteractionOption::ToggleSelectOption(bool selected)
{
	OptionBG->SetVisibility(selected ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
}
