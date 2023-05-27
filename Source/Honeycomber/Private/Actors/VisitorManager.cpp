// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VisitorManager.h"
#include "Components/SplineComponent.h"
#include "Actors/Visitors/Visitor.h"
#include "Actors/Interactables/Desk.h"
#include "Actors/ResourceManager.h"

// Sets default values
AVisitorManager::AVisitorManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	check(SceneRoot);
	SetRootComponent(SceneRoot);

	VisitorSpline = CreateDefaultSubobject<USplineComponent>("VisitorSpline");
	check(VisitorSpline);
	VisitorSpline->SetupAttachment(SceneRoot);
}

void AVisitorManager::Tick(float DeltaSeconds)
{
	if (CurrentVisitor && !CurrentVisitorSplineMovementDone)
	{
		CurrentVisitorSplineProgress += (DeltaSeconds * CurrentVisitorSplineDirection);
		CurrentVisitor->SetActorTransform(VisitorSpline->GetTransformAtTime(CurrentVisitorSplineProgress, ESplineCoordinateSpace::World));

		if(CurrentVisitorSplineDirection > 0 && CurrentVisitorSplineProgress >= VisitorSplineDuration)
		{
			CurrentVisitorSplineMovementDone = true;
			CurrentVisitor->StartTalking();
			SaleDesk->UpdateDeskOptions(CurrentVisitor->GetOptions(), ResourceManager->HaveEnoughResources(EResourceType::HONEY, 2));
		}
		else if (CurrentVisitorSplineDirection < 0 && CurrentVisitorSplineProgress <= 0)
		{
			CurrentVisitorSplineMovementDone = true;
			SpawnVisitor();
		}
	}
}

// Called when the game starts or when spawned
void AVisitorManager::BeginPlay()
{
	Super::BeginPlay();
	VisitorSplineLength = VisitorSpline->GetSplineLength();
	VisitorSpline->Duration = VisitorSplineDuration;

	ResourceManager->OnUpdatedResourceDelegate.BindUObject(this, &AVisitorManager::ResourcesUpdated);
	SaleDesk->OnVisitorResponseDelegate.BindUObject(this, &AVisitorManager::ResponsePicked);

	SpawnVisitor();
}

void AVisitorManager::SpawnVisitor()
{
	if (CurrentVisitor)
	{
		CurrentVisitor->Destroy();
	}
	CurrentVisitorSplineProgress = 0;
	CurrentVisitorSplineDirection = 1;
	CurrentVisitorSplineMovementDone = false;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, false);
	CurrentVisitor = GetWorld()->SpawnActor<AVisitor>(VisitorClass, VisitorSpline->GetTransformAtSplinePoint(0, ESplineCoordinateSpace::World), SpawnInfo);
	CurrentVisitor->SetupVisitor(EVisitorype::CUSTOMER, "TestCustomer");
}

void AVisitorManager::ResourcesUpdated(EResourceType resourceType, int32 numResources)
{
	if (CurrentVisitor && CurrentVisitorSplineMovementDone)
	{
		SaleDesk->UpdateDeskOptions(CurrentVisitor->GetOptions(), ResourceManager->HaveEnoughResources(EResourceType::HONEY, 2));
	}
}

void AVisitorManager::ResponsePicked(int32 optionIndex)
{
	if(optionIndex == 0)
	{
		ResourceManager->TryAddingResources(EResourceType::HONEY, -2);
		ResourceManager->AddMoney(10);
	}

	CurrentVisitor->StopTalking();
	SaleDesk->ClearDeskOptions();
	CurrentVisitorSplineMovementDone = false;
	CurrentVisitorSplineDirection = -1;
}

