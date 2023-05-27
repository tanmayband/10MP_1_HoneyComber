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
	if (CurrentVisitor && CurrentVisitorSplineProgress < VisitorSplineDuration)
	{
		CurrentVisitorSplineProgress += DeltaSeconds;
		CurrentVisitor->SetActorTransform(VisitorSpline->GetTransformAtTime(CurrentVisitorSplineProgress, ESplineCoordinateSpace::World));
		if (CurrentVisitorSplineProgress >= VisitorSplineDuration)
		{
			CurrentVisitor->StartTalking();
			SaleDesk->UpdateDeskOptions(CurrentVisitor->GetOptions(), ResourceManager->HaveEnoughResources(EResourceType::HONEY, 2));
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
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, false);
	CurrentVisitor = GetWorld()->SpawnActor<AVisitor>(VisitorClass, VisitorSpline->GetTransformAtSplinePoint(0, ESplineCoordinateSpace::World), SpawnInfo);
}

void AVisitorManager::ResourcesUpdated(EResourceType resourceType, int32 numResources)
{
	if (CurrentVisitor)
	{
		SaleDesk->UpdateDeskOptions(CurrentVisitor->GetOptions(), ResourceManager->HaveEnoughResources(EResourceType::HONEY, 2));
	}
}

void AVisitorManager::ResponsePicked(int32 optionIndex)
{
	ResourceManager->TryAddingResources(EResourceType::HONEY, -2);
}

