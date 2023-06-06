// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/FrameAcceptor.h"
#include "Utils/Structs.h"
#include "InventorySubsystem.generated.h"

class UFrameInventory;

UCLASS()
class HONEYCOMBER_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitializeInventory(TSubclassOf<UFrameInventory> inventoryClass);
	void SetFrameAcceptor(IFrameAcceptor* newFrameAcceptor);
	bool AddFrameToInventory(FBeeFrameData frameData);

private:
	UFrameInventory* FrameInventory;
	IFrameAcceptor* CurrentFrameAcceptor;
	TArray<FBeeFrameData> FramesData;

	void ToggleInventory(bool show);
	bool RemoveFrameFromInventory(uint8 frameIndex);
};
