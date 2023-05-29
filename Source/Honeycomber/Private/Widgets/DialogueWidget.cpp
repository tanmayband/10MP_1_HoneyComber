// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DialogueWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UDialogueWidget::SetupDialogueWidget(FVector2D pivot)
{
	UCanvasPanelSlot* ContainerSlot = Cast<UCanvasPanelSlot>(Container->Slot);
	ContainerSlot->SetAnchors(FAnchors(0, 1, pivot.Y, pivot.Y));
	ContainerSlot->SetAlignment(pivot);
}

void UDialogueWidget::UpdateDialogueLine(FString dialogueLine)
{
	DialogueText->SetText(FText::FromString(dialogueLine));
}

void UDialogueWidget::SetDialogueBGColour(FLinearColor newBGColour)
{
	DialogueBG->SetColorAndOpacity(newBGColour);
}
