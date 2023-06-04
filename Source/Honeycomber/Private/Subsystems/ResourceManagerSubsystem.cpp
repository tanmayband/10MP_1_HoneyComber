// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ResourceManagerSubsystem.h"
#include "Actors/Interactables/Beehive.h"
#include "Actors/ResourceStorage.h"
#include "Actors/MoneyStorage.h"
#include "Subsystems/MoneyFlowSubsystem.h"

void UResourceManagerSubsystem::RegisterStorage(EResourceType resourceType, AResourceStorage* storage)
{
	switch (resourceType)
	{
		case EResourceType::HONEY:
		{
			if (!HoneyStores.Contains(storage))
			{
				HoneyStores.Add(storage);
			}
			break;
		}
		case EResourceType::WAX:
		{
			if (!WaxStores.Contains(storage))
			{
				WaxStores.Add(storage);
			}
			break;
		}
	}
}

uint8 UResourceManagerSubsystem::TryAddingResources(EResourceType resourceType, int16 numResources)
{
	uint8 resourcesToAdd = numResources;
	TArray<AResourceStorage*> resourcesToCheck;
	switch (resourceType)
	{
	case EResourceType::HONEY:
	{
		resourcesToCheck = HoneyStores;
		break;
	}
	case EResourceType::WAX:
	{
		resourcesToCheck = WaxStores;
		break;
	}
	}

	for (AResourceStorage* storage : resourcesToCheck)
	{
		int16 spaceAvailable = storage->GetAvailableSpace();
		int16 resourcesCanBeFit = FMath::Min(spaceAvailable, numResources);
		storage->ModifyResourceAmount(resourcesCanBeFit);
		numResources -= resourcesCanBeFit;
	}

	// how many added eventually?
	uint8 resourcesAdded = resourcesToAdd - numResources;
	ResourcesData[resourceType] += resourcesAdded;
	OnUpdatedResourceDelegate.ExecuteIfBound(resourceType, ResourcesData[resourceType]);
	return resourcesAdded;
}

void UResourceManagerSubsystem::SellResource(EResourceType resourceType, uint8 numResources)
{
	TryAddingResources(resourceType, -numResources);
	UMoneyFlowSubsystem* moneySubsystem = GetGameInstance()->GetSubsystem<UMoneyFlowSubsystem>();
	moneySubsystem->MoneyAdded(ResourcesCost[resourceType] * numResources);
}

bool UResourceManagerSubsystem::HaveEnoughResources(EResourceType resourceType, uint8 numResources)
{
	return ResourcesData[resourceType] >= numResources;
}

void UResourceManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}
