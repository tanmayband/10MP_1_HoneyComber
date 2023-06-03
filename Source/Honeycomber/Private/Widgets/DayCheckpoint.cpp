// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DayCheckpoint.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"

void UDayCheckpoint::SetupCheckpoint(uint8 dayNum)
{
	BGMaterial = IrisBG->GetDynamicMaterial();
	SetBGRadius(0);
}

void UDayCheckpoint::UpdateDayCount()
{

}

void UDayCheckpoint::StartDayAnim()
{
	PlayAnimation(DayIn);
}

void UDayCheckpoint::EndDayAnim()
{
	
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
