// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Visitors/Visitor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/StateDisplay.h"

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

	VisitorDisplayComponent = CreateDefaultSubobject<UWidgetComponent>("VisitorDisplay");
	check(VisitorDisplayComponent);
	VisitorDisplayComponent->SetupAttachment(SceneRoot);
	VisitorDisplayComponent->SetWidgetSpace(EWidgetSpace::Screen);
	ToggleStateDisplay(false);
}

void AVisitor::SetupVisitor(EVisitorype visitorType, FString visitorName)
{
	VisitorType = visitorType;
	VisitorName = visitorName;
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

void AVisitor::ToggleStateDisplay(bool show)
{
	VisitorDisplayComponent->SetHiddenInGame(!show);
}

void AVisitor::ProcessOption(int32 optionIndex)
{
}

void AVisitor::StartTalking()
{
	ToggleStateDisplay(true);
}

// Called when the game starts or when spawned
void AVisitor::BeginPlay()
{
	Super::BeginPlay();
	VisitorDisplay = CastChecked<UStateDisplay, UUserWidget>(VisitorDisplayComponent->GetUserWidgetObject());
	VisitorDisplay->SetupState("Hi, can I have 2 jars of honey?", "");
}

