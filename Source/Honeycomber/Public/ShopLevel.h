// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Utils/Enums.h"
#include "ShopLevel.generated.h"

class AComberCharacter;
class AInteractable;
class ABeehive;
class AResourceStorage;

UCLASS()
class HONEYCOMBER_API AShopLevel : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

private:
	AComberCharacter* ComberCharacter;
};
