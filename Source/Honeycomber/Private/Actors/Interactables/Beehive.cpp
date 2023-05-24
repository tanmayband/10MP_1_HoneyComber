// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Beehive.h"
#include "Components/StaticMeshComponent.h"

ABeehive::ABeehive()
{
	PrimaryActorTick.bCanEverTick = true;
	BeehiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeehiveMesh"));
	check(BeehiveMesh)
	BeehiveMesh->SetupAttachment(SceneRoot);
}

void ABeehive::Tick(float DeltaSeconds)
{
	if (CurrentHoneyJars < MaxHoneyJars)
	{
		float honeyThisTick = HoneyJarRatePerBee * NumBees * DeltaSeconds;
		CurrentHoneyJars = FMath::Clamp(CurrentHoneyJars + honeyThisTick, 0, (float)MaxHoneyJars);
	}
}

int32 ABeehive::GetCurrentHoneyJars()
{
	return CurrentHoneyJars;
}

void ABeehive::InteractOption(int32 index)
{
	switch (index)
	{
		case 0:
		{
			UE_LOG(LogTemp, Warning, TEXT("Got honey"));
			break;
		}
		case 1:
		{
			UE_LOG(LogTemp, Warning, TEXT("Got wax"));
			break;
		}
	default:
		break;
	}
}
