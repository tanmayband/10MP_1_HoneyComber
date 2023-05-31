// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Beehive.h"
#include "Components/StaticMeshComponent.h"
#include "Widgets/InteractionPopup.h"
#include "Components/WidgetComponent.h"
#include "Widgets/StateDisplay.h"

ABeehive::ABeehive()
{
	PrimaryActorTick.bCanEverTick = true;
	BeehiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeehiveMesh"));
	check(BeehiveMesh)
	BeehiveMesh->SetupAttachment(SceneRoot);

	HoneyDisplayComponent = CreateDefaultSubobject<UWidgetComponent>("HoneyDisplay");
	check(HoneyDisplayComponent);
	HoneyDisplayComponent->SetupAttachment(SceneRoot);
	HoneyDisplayComponent->SetWidgetSpace(EWidgetSpace::Screen);

	WaxDisplayComponent = CreateDefaultSubobject<UWidgetComponent>("WaxDisplay");
	check(WaxDisplayComponent);
	WaxDisplayComponent->SetupAttachment(SceneRoot);
	WaxDisplayComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void ABeehive::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	HoneyDisplayComponent->SetWidgetClass(StateDisplayClass);
	WaxDisplayComponent->SetWidgetClass(StateDisplayClass);
}

void ABeehive::Tick(float DeltaSeconds)
{
	if (CurrentHoneyJars < MaxHoneyJars)
	{
		float honeyThisTick = HoneyJarRatePerBee * NumBees * DeltaSeconds;
		CurrentHoneyJars = FMath::Clamp(CurrentHoneyJars + honeyThisTick, 0, (float)MaxHoneyJars);
	}
	HoneyDisplay->UpdateState(FString::Printf(TEXT("%d"), (int)CurrentHoneyJars));

	if (CurrentWaxJars < MaxWaxJars)
	{
		float waxThisTick = WaxJarRatePerBee * NumBees * DeltaSeconds;
		CurrentWaxJars = FMath::Clamp(CurrentWaxJars + waxThisTick, 0, (float)MaxWaxJars);
	}
	WaxDisplay->UpdateState(FString::Printf(TEXT("%d"), (int)CurrentWaxJars));
}

uint8 ABeehive::GetCurrentHoneyJars()
{
	return CurrentHoneyJars;
}

void ABeehive::InteractOption(uint8 index)
{
	Super::InteractOption(index);
	switch (index)
	{
	case 0:
	{
		if (CurrentHoneyJars > 1)
		{
			if (ExtractedResourceDelegate.IsBound())
			{
				CurrentHoneyJars -= ExtractedResourceDelegate.Execute(EResourceType::HONEY, FMath::Min(HoneyExtractAmount, CurrentHoneyJars));
			}
		}
		break;
	}
	case 1:
	{
		if (CurrentWaxJars > 1)
		{
			if (ExtractedResourceDelegate.IsBound())
			{
				CurrentWaxJars -= ExtractedResourceDelegate.Execute(EResourceType::WAX, FMath::Min(WaxExtractAmount, CurrentWaxJars));
			}
		}
		break;
	}
	default:
		break;
	}
}

void ABeehive::DisableExtraction(EResourceType resourceType)
{
	switch (resourceType)
	{
	case EResourceType::HONEY:
	{
		InteractionPopup->ToggleOptionEnabled(0, false);
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

void ABeehive::UpdateBees()
{
	// how many bees can sustain in current honey
	uint8 possibleBees = CurrentHoneyJars * NumBeesRequiringOneJar;
	uint8 survivingBees = FMath::Min(NumBees, possibleBees);
	
	// TODO: tell some widget how many bees died (NumBees - survivingBees)

	// update current bees
	NumBees = survivingBees;
}

void ABeehive::BeginPlay()
{
	Super::BeginPlay();

	HoneyDisplay = CastChecked<UStateDisplay, UUserWidget>(HoneyDisplayComponent->GetUserWidgetObject());
	WaxDisplay = CastChecked<UStateDisplay, UUserWidget>(WaxDisplayComponent->GetUserWidgetObject());
	HoneyDisplay->SetupState("Honey jars:", "0");
	WaxDisplay->SetupState("Wax jars:", "0");

	StartContinuousDamage(5, 20);
}

void ABeehive::ProcessHeal()
{
	if (CurrentHealth >= MaxHealth)
	{
		// restart damage when reached max health
		StartContinuousDamage(5, 20);
	}
}
