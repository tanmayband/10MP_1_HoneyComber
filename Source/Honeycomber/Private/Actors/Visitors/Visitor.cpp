// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Visitors/Visitor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/DialogueWidget.h"

// Sets default values
AVisitor::AVisitor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	check(SceneRoot);
	SetRootComponent(SceneRoot);

	VisitorMesh = CreateDefaultSubobject<UStaticMeshComponent>("VisitorMesh");
	check(VisitorMesh)
	VisitorMesh->SetupAttachment(SceneRoot);

	VisitorDialogueComponent = CreateDefaultSubobject<UWidgetComponent>("VisitorDialogue");
	check(VisitorDialogueComponent);
	VisitorDialogueComponent->SetupAttachment(SceneRoot);
	VisitorDialogueComponent->SetWidgetSpace(EWidgetSpace::Screen);
	VisitorDialogueComponent->SetRelativeLocation(FVector(-150, 0, 0));
	ToggleDialogueDisplay(false);
}

void AVisitor::SetupVisitor(FVisitorData visitorData)
{
	VisitorName = visitorData.VisitorName;
	VisitorType = visitorData.VisitorType;
	VisitorDialogueTable = visitorData.VisitorDialogueTable;

	VisitorDialogue = CastChecked<UDialogueWidget, UUserWidget>(VisitorDialogueComponent->GetUserWidgetObject());
	VisitorDialogue->SetupDialogueWidget(FVector2D(0.5, 1));
	VisitorDialogueComponent->SetPivot(FVector2D(0.5, 1));
	//VisitorDialogue->SetDialogueBGColour();
}

void AVisitor::UpdateOptions(TArray<FString> responseOptions)
{
	ResponseOptions.Empty();
	ResponseOptions = responseOptions;
}

TArray<FString> AVisitor::GetOptions()
{
	return ResponseOptions;
}

void AVisitor::ToggleDialogueDisplay(bool show)
{
	VisitorDialogueComponent->SetHiddenInGame(!show);
}

void AVisitor::ProcessOption(uint8 optionIndex)
{
}

UDataTable* AVisitor::StartTalking()
{
	return VisitorDialogueTable;
}

void AVisitor::DisplayDialogueLine(FString dialogueLine)
{
	VisitorDialogue->UpdateDialogueLine(dialogueLine);
	ToggleDialogueDisplay(true);
}

void AVisitor::StopTalking()
{
	ToggleDialogueDisplay(false);
}

// Called when the game starts or when spawned
void AVisitor::BeginPlay()
{
	Super::BeginPlay();
}

