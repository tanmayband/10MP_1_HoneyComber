// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FrameInventory.h"
#include "Widgets/InteractionPopup.h"
#include "Widgets/InteractionOption.h"

void UFrameInventory::SetupInventory()
{
	FrameList->SetupPopup("Frame Inventory", FramesData, FVector2D(0.5, 0));
	FrameList->OnOptionSelectedDelegate.BindUObject(this, &UFrameInventory::RemoveFrame);
}

void UFrameInventory::AddFrame(FBeeFrameData frameData)
{
	if (FramesData.Num() < 8)
	{
		FInteractionOptionEnabled newFrameOption = FInteractionOptionEnabled(FString::Printf(TEXT("%s frame (%d%% full)"), *ActionPrefixes[CurrentAction], frameData.HoneyFill), true);
		FramesData.Add(newFrameOption);

		FrameList->SetupPopupOptions(FramesData);
	}
}

bool UFrameInventory::IsInventoryFull()
{
	return FramesData.Num() >= 8;
}

void UFrameInventory::RemoveFrame(uint8 frameIndex)
{
	if(OnFrameRemoveRequestDelegate.IsBound())
	{
		if (OnFrameRemoveRequestDelegate.Execute(frameIndex))
		{
			FramesData.RemoveAt(frameIndex);
			FrameList->SetupPopupOptions(FramesData);
		}
	}
}
