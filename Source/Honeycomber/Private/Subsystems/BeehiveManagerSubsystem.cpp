// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/BeehiveManagerSubsystem.h"
#include "Actors/Interactables/Beehive.h"

void UBeehiveManagerSubsystem::RegisterBeehive(ABeehive* beehive)
{
	if (!Beehives.Contains(beehive))
	{
		Beehives.Add(beehive);
	}
}

uint8 UBeehiveManagerSubsystem::GetAllBees()
{
	uint8 beesNum(0);
	for (ABeehive* beehive : Beehives)
	{
		beesNum += beehive->GetBees();
	}
	return beesNum;
}

uint8 UBeehiveManagerSubsystem::UpdateAllBees()
{
	uint8 beesNum(0);
	for (ABeehive* beehive : Beehives)
	{
		beehive->UpdateBees();
		beesNum += beehive->GetBees();
	}
	return beesNum;
}
