// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StateDisplay.h"
#include "Components/TextBlock.h"

void UStateDisplay::SetupState(FString stateName, FString initialStateValue)
{
	StateName->SetText(FText::FromString(stateName));
	UpdateState(initialStateValue);
}

void UStateDisplay::UpdateState(FString newStateValue)
{
	StateValue->SetText(FText::FromString(newStateValue));
}
