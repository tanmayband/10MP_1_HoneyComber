// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopLevel.h"
#include "Actors/Interactables//Beehive.h"

void AShopLevel::BeginPlay()
{
	for (ABeehive* beehive : Beehives)
	{
		beehive->ExtractedResourceDelegate.BindUObject(this, &AShopLevel::StoreResource);
	}
}

void AShopLevel::StoreResource(EResourceType resourceType)
{
	switch (resourceType)
	{
		case EResourceType::HONEY:
		{
			honeyJars += 1;
			HoneyStore->SetInteractableName(FString::Printf(TEXT("Honey: %d jars"), honeyJars));
			break;
		}
		case EResourceType::WAX:
		{
			break;
		}
		default:
			break;
	}
}
