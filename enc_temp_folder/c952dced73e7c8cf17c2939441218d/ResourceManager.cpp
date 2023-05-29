// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ResourceManager.h"
#include "Actors/Interactables/Beehive.h"
#include "Actors/ResourceStorage.h"
#include "Actors/MoneyStorage.h"

// Sets default values
AResourceManager::AResourceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

bool AResourceManager::HaveEnoughResources(EResourceType resourceType, uint8 numResources)
{
	return ResourcesData[resourceType] >= numResources;
}

void AResourceManager::AddMoney(uint8 numMoney)
{
	MoneyStore->AddMoney(numMoney);
}

// Called when the game starts or when spawned
void AResourceManager::BeginPlay()
{
	Super::BeginPlay();
	for (ABeehive* beehive : Beehives)
	{
		beehive->ExtractedResourceDelegate.BindUObject(this, &AResourceManager::TryAddingResources);
	}
}

uint8 AResourceManager::TryAddingResources(EResourceType resourceType, int16 numResources)
{
	UE_LOG(LogTemp, Warning, TEXT("TryAddingResources %d"), numResources);
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

void AResourceManager::SellResource(EResourceType resourceType, uint8 numResources)
{
	UE_LOG(LogTemp, Warning, TEXT("SellResource %d"), numResources);
	TryAddingResources(resourceType, -numResources);
	AddMoney(ResourcesCost[resourceType] * numResources);
}

