// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums.h"
#include "ResourceManager.generated.h"

class ABeehive;
class AResourceStorage;
class AMoneyStorage;

DECLARE_DELEGATE_TwoParams(FUpdatedResourceSignature, EResourceType resourceType, uint8 resourceAmount)

UCLASS()
class HONEYCOMBER_API AResourceManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AResourceManager();
	uint8 TryAddingResources(EResourceType resourceType, uint8 numResources);
	void SellResource(EResourceType resourceType, uint8 numResources);
	bool HaveEnoughResources(EResourceType resourceType, uint8 numResources);
	void AddMoney(uint8 numMoney);
	TMap<EResourceType, uint8> GetResourcesData() { return ResourcesData; };
	FUpdatedResourceSignature OnUpdatedResourceDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TArray<ABeehive*> Beehives;
	UPROPERTY(EditAnywhere)
		TArray<AResourceStorage*> HoneyStores;
	UPROPERTY(EditAnywhere)
		TArray<AResourceStorage*> WaxStores;
	UPROPERTY(EditAnywhere)
		AMoneyStorage* MoneyStore;

	TMap<EResourceType, uint8> ResourcesData = {
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