// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractionPopup.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Widgets/InteractionOption.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UInteractionPopup::SetupPopup(FString PopupName, TArray<FString> PopupOptions, FVector2D PopupPivot)
{
	SetupPopupName(PopupName);
	UCanvasPanelSlot* ContainerSlot = Cast<UCanvasPanelSlot>(Container->Slot);
	ContainerSlot->SetAnchors(FAnchors(PopupPivot.X, PopupPivot.Y));
	ContainerSlot->SetAlignment(PopupPivot);;
	SetupPopupOptions(PopupOptions);
	
	//HighlightInteractionOption(0);
}

void UInteractionPopup::SetupPopupName(FString PopupName)
{
	InteractableName->SetText(FText::FromString(PopupName));
}

void UInteractionPopup::SetupPopupOptions(TArray<FString> PopupOptions)
{
	ClearOptions();
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

void UInteractionPopup::ToggleOptionEnabled(int32 optionIndex, bool enabled)
{
	AllOptions[optionIndex]->ToggleClickableOption(enabled);
}

void UInteractionPopup::ClearOptions()
{
	for (UUserWidget* optionWidget : AllOptions)
	{
		if (optionWidget)
		{
			//optionWidget->OnOptionSelectedDelegate.Unbind();
			optionWidget->RemoveFromParent();
		}
	}
	AllOptions.Empty();
}

void UInteractionPopup::InteractionOptionSelected(int32 optionIndex)
{
	OnOptionSelectedDelegate.ExecuteIfBound(optionIndex);
}
