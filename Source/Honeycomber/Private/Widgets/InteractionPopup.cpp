// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractionPopup.h"
#include "Components/TextBlock.h"
#include "Widgets/InteractionOption.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UInteractionPopup::SetupPopup(FString PopupName, TArray<FString> PopupOptions)
{
	ClearOptions();
	InteractableName->SetText(FText::FromString(PopupName));

	int32 iOption(0);
	for (FString option : PopupOptions)
	{
		UInteractionOption* newOption = CreateWidget<UInteractionOption>(GetWorld()->GetFirstPlayerController(), InteractionOptionClass);
		newOption->SetupOption(option, iOption);
		OptionsBox->AddChildToVerticalBox(newOption);
		UVerticalBoxSlot* newOptionSlot = Cast<UVerticalBoxSlot>(newOption->Slot);
		newOptionSlot->SetPadding(FMargin(0, 10, 0, 0));

		newOption->OnOptionSelectedDelegate.BindUObject(this, &UInteractionPopup::InteractionOptionSelected);

		AllOptions.Add(newOption);
		iOption++;
	}
	//HighlightInteractionOption(0);
}

void UInteractionPopup::HighlightInteractionOption(int32 optionIndex)
{
	UnhighlightAllInteractionOptions();
	if (AllOptions.Num() > 0)
	{
		AllOptions[optionIndex]->ToggleHighlightOption(true);
	}
}

void UInteractionPopup::UnhighlightAllInteractionOptions()
{
	for (UInteractionOption* optionWidget : AllOptions)
	{
		optionWidget->ToggleHighlightOption(false);
	}
}

void UInteractionPopup::ClearOptions()
{
	for (UUserWidget* optionWidget : AllOptions)
	{
		if (optionWidget)
		{
			optionWidget->RemoveFromParent();
		}
	}
	AllOptions.Empty();
}

void UInteractionPopup::InteractionOptionSelected(int32 optionIndex)
{
	OnOptionSelectedDelegate.ExecuteIfBound(optionIndex);
}
