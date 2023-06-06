// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/InventorySubsystem.h"
#include "Widgets/FrameInventory.h"
#include "Kismet/GameplayStatics.h"

void UInventorySubsystem::InitializeInventory(TSubclassOf<UFrameInventory> inventoryClass)
{
	FrameInventory = CreateWidget<UFrameInventory>(UGameplayStatics::GetPlayerController(GetWorld(), 0), inventoryClass);
	FrameInventory->SetupInventory();
	FrameInventory->OnFrameRemoveRequestDelegate.BindUObject(this, &UInventorySubsystem::RemoveFrameFromInventory);
}

void UInventorySubsystem::ToggleInventory(bool show)
{
	if(show)
		FrameInventory->AddToViewport();
	else
		FrameInventory->RemoveFromParent();
}

bool UInventorySubsystem::RemoveFrameFromInventory(uint8 frameIndex)
{
	bool isFrameRemoved = CurrentFrameAcceptor->AcceptFrame(FramesData[frameIndex]);
	if(isFrameRemoved)
		FramesData.RemoveAt(frameIndex);
	return isFrameRemoved;
}

void UInventorySubsystem::SetFrameAcceptor(IFrameAcceptor* newFrameAcceptor)
{
	CurrentFrameAcceptor = newFrameAcceptor;
	if (!CurrentFrameAcceptor)
		ToggleInventory(false);
	else
	{
		switch (CurrentFrameAcceptor->GetAcceptorType())
		{
			case EFrameAcceptorType::BEEHIVE:
			{
				FrameInventory->CurrentAction = EFrameActionType::PUT_BACK;
				break;
			}
			case EFrameAcceptorType::DRAINER:
			{
				FrameInventory->CurrentAction = EFrameActionType::SCRAPE_DUMP;
				break;
			}
			case EFrameAcceptorType::CENTRIFUGE:
			{
				FrameInventory->CurrentAction = EFrameActionType::SCRAPE_INSERT;
				break;
			}
		}
		ToggleInventory(true);
	}
}

bool UInventorySubsystem::AddFrameToInventory(FBeeFrameData frameData)
{
	bool isFrameAdded(false);
	if (!FrameInventory->IsInventoryFull())
	{
		isFrameAdded = true;
		FramesData.Add(frameData);
		FrameInventory->AddFrame(frameData);
	}
	return isFrameAdded;
}

