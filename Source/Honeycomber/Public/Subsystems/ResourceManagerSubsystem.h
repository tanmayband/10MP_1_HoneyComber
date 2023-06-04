// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Utils/Enums.h"
#include "ResourceManagerSubsystem.generated.h"

class AResourceStorage;
class AMoneyStorage;
class ADamageableInteractable;

DECLARE_DELEGATE_TwoParams(FUpdatedResourceSignature, EResourceType resourceType, uint8 resourceAmount)

UCLASS()
class HONEYCOMBER_API UResourceManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void RegisterStorage(EResourceType resourceType, AResourceStorage* storage);
	uint8 TryAddingResources(EResourceType resourceType, int16 numResources);
	void SellResource(EResourceType resourceType, uint8 numResources);
	bool HaveEnoughResources(EResourceType resourceType, uint8 numResources);
	TMap<EResourceType, uint16> GetResourcesData() { return ResourcesData; };
	FUpdatedResourceSignature OnUpdatedResourceDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	TArray<AResourceStorage*> HoneyStores;
	TArray<AResourceStorage*> WaxStores;

	TMap<EResourceType, uint16> ResourcesData = {
		{EResourceType::HONEY, 0},
		{EResourceType::WAX, 0},
		{EResourceType::ITEM, 0}
	};

	TMap<EResourceType, uint8> ResourcesCost = {
		{EResourceType::HONEY, 10},
		{EResourceType::WAX, 5},
		{EResourceType::ITEM, 0}
	};
};
