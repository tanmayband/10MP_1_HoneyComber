// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DayCheckpoint.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"

void UDayCheckpoint::SetupCheckpoint(uint8 dayNum)
{
	BGMaterial = IrisBG->GetDynamicMaterial();
	SetBGRadius(0);
	DayText->SetText(FText::FromString(FString::Printf(TEXT("Day %d"), dayNum)));
}

void UDayCheckpoint::UpdateDayCount()
{

}

void UDayCheckpoint::StartDayAnim()
{
	PlayAnimationForward(DayIn);
}

void UDayCheckpoint::EndDayAnim()
{
	PlayAnimationForward(DayOut);
}

void UDayCheckpoint::SetBGRadius(float newRadius)
{
	CurrentBGRadius = FMath::Clamp(newRadius,0,1);
	BGMaterial->SetScalarParameterValue("Radius", CurrentBGRadius);
}

void UDayCheckpoint::StartDayAnimDone()
{
	OnDayAnimDoneDelegate.ExecuteIfBound(true);
}

void UDayCheckpoint::EndDayAnimDone()
{
	OnDayAnimDoneDelegate.ExecuteIfBound(false);
}
