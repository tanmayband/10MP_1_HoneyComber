// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BeehiveManagerSubsystem.generated.h"

class ABeehive;

UCLASS()
class HONEYCOMBER_API UBeehiveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void RegisterBeehive(ABeehive* beehive);
	uint8 GetAllBees();
	uint8 UpdateAllBees();

private:
	TArray<ABeehive*> Beehives;
};
