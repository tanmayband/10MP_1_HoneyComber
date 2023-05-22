// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractionPopup.h"
#include "Components/TextBlock.h"

void UInteractionPopup::SetupPopup(FString PopupName)
{
	InteractableName->SetText(FText::FromString(PopupName));
}
