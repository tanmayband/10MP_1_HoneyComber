// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ResourceStorage.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/StateDisplay.h"
#include "Utils/Utils.h"

// Sets default values
AResourceStorage::AResourceStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	check(SceneRoot);
	SetRootComponent(SceneRoot);

	StorageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StorageMesh"));
	check(StorageMesh)
	StorageMesh->SetupAttachment(SceneRoot);

	ResourceDisplayComponent = CreateDefaultSubobject<UWidgetComponent>("ResourceDisplay");
	check(ResourceDisplayComponent);
	ResourceDisplayComponent->SetupAttachment(SceneRoot);
	ResourceDisplayComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void AResourceStorage::OnConstruction(const FTransform& Transform)
{
	
}

void AResourceStorage::SetupResourceStorage(EResourceType resourceType, uint8 maxAmount, uint8 currentAmount)
{
	ResourceType = resourceType;
	MaxResourceAmount = maxAmount;
	CurrentResourceAmount = currentAmount;
}

void AResourceStorage::ModifyResourceAmount(int16 amountDelta)
{
	CurrentResourceAmount = FMath::Clamp(CurrentResourceAmount + amountDelta, 0, MaxResourceAmount);
	ResourceDisplay->UpdateState(FString::Printf(TEXT("%d jars"), CurrentResourceAmount));
}

uint8 AResourceStorage::GetAvailableResources()
{
	return CurrentResourceAmount;
}

uint8 AResourceStorage::GetAvailableSpace()
{
	return MaxResourceAmount - CurrentResourceAmount;
}

// Called when the game starts or when spawned
void AResourceStorage::BeginPlay()
{
	Super::BeginPlay();
	ResourceName = EnumUtils::GetResourceName(ResourceType);
	ResourceDisplay = CastChecked<UStateDisplay, UUserWidget>(ResourceDisplayComponent->GetUserWidgetObject());
	ResourceDisplay->SetupState(FString::Printf(TEXT("%s:"), *ResourceName), "0 jars");
}

