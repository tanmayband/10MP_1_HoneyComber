// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopLevel.h"
#include "Actors/Interactables//Beehive.h"
#include "Actors/ResourceStorage.h"

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
			HoneyStore->ModifyResourceAmount(1);
			break;
		}
		case EResourceType::WAX:
		{
			WaxStore->ModifyResourceAmount(1);
			break;
		}
		default:
			break;
	}
}
