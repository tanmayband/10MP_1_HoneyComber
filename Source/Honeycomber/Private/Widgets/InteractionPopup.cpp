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

	for (FString option : PopupOptions)
	{
		UInteractionOption* newOption = CreateWidget<UInteractionOption>(GetWorld()->GetFirstPlayerController(), InteractionOptionClass);
		newOption->SetupOption(option);
		OptionsBox->AddChildToVerticalBox(newOption);
		UVerticalBoxSlot* newOptionSlot = Cast<UVerticalBoxSlot>(newOption->Slot);
		newOptionSlot->SetPadding(FMargin(0, 10, 0, 0));
		AllOptions.Add(newOption);
	}
	SelectInteractionOption(0);
}

void UInteractionPopup::SelectInteractionOption(int32 optionIndex)
{
	if (AllOptions.Num() > 0)
	{
		for (UInteractionOption* optionWidget : AllOptions)
		{
			optionWidget->ToggleSelectOption(false);
		}
		AllOptions[optionIndex]->ToggleSelectOption(true);
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
