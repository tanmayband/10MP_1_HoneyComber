// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VisitorManager.h"
#include "Components/SplineComponent.h"
#include "Actors/Visitors/Visitor.h"
#include "Actors/Interactables/Desk.h"
#include "Actors/ResourceManager.h"
#include "Actors/Dialogues/DialogueManager.h"

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
			FString currentDialogueText = DialogueManager->StartDialogue(CurrentVisitor->StartTalking(), "1");
			DisplayDialogue(currentDialogueText);
		}
		else if (CurrentVisitorSplineDirection < 0 && CurrentVisitorSplineProgress <= 0)
		{
			CurrentVisitorSplineMovementDone = true;
			OnVisitorDoneDelegate.ExecuteIfBound();
		}
	}
}

void AVisitorManager::SetupVisitorManager()
{
	VisitorSplineLength = VisitorSpline->GetSplineLength();
	VisitorSpline->Duration = VisitorSplineDuration;

	ResourceManager->OnUpdatedResourceDelegate.BindUObject(this, &AVisitorManager::ResourcesUpdated);
	SaleDesk->OnVisitorResponseDelegate.BindUObject(this, &AVisitorManager::ResponsePicked);

	DialogueManager->SetupDialogueManager(ResourceManager->GetResourcesData());
	DialogueManager->OnEventGivenDelegate.BindUObject(ResourceManager, &AResourceManager::SellResource);
}

void AVisitorManager::SetupNewVisitor(FVisitorData visitorData)
{
	SpawnVisitor(visitorData);
}

// Called when the game starts or when spawned
void AVisitorManager::BeginPlay()
{
	Super::BeginPlay();
}

void AVisitorManager::SpawnVisitor(FVisitorData visitorData)
{
	CurrentVisitorSplineProgress = 0;
	CurrentVisitorSplineDirection = 1;
	CurrentVisitorSplineMovementDone = false;
	if (!CurrentVisitor)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, false);
		CurrentVisitor = GetWorld()->SpawnActor<AVisitor>(VisitorClass, VisitorSpline->GetTransformAtSplinePoint(0, ESplineCoordinateSpace::World), SpawnInfo);
	}
	CurrentVisitor->SetupVisitor(visitorData);
}

void AVisitorManager::ResourcesUpdated(EResourceType resourceType, uint8 numResources)
{
	DialogueManager->UpdateResourcesState(resourceType, numResources);
	if (CurrentVisitor && CurrentVisitorSplineMovementDone)
		SaleDesk->UpdateDeskOptions(DialogueManager->GetOptions());
}

void AVisitorManager::DisplayDialogue(FString dialogueLine)
{
	CurrentVisitor->DisplayDialogueLine(dialogueLine);
	TArray<FInteractionOptionEnabled> nextOptions = DialogueManager->GetOptions();
	if(nextOptions.Num() > 0)
	{
		SaleDesk->UpdateDeskOptions(nextOptions);
	}
	else
	{
		// TODO: add a timer to show the line and then start moving out (based on line length maybe)
		DoneTalking();
	}
}

void AVisitorManager::ResponsePicked(uint8 optionIndex)
{
	FString nextDialogueText = DialogueManager->PickOption(optionIndex);

	if (nextDialogueText.IsEmpty())
	{
		DoneTalking();
	}
	else
	{
		DisplayDialogue(nextDialogueText);
	}
}

void AVisitorManager::DoneTalking()
{
	CurrentVisitor->StopTalking();
	SaleDesk->ClearDeskOptions();
	CurrentVisitorSplineMovementDone = false;
	CurrentVisitorSplineDirection = -1;
}

