// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Interactable.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/InteractionPopup.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	check(SceneRoot);
	SetRootComponent(SceneRoot);
	
	InteractionArea = CreateDefaultSubobject<UBoxComponent>("InteractionArea");
	check(InteractionArea);
	InteractionArea->SetupAttachment(SceneRoot);
	InteractionArea->SetBoxExtent(FVector(50, 50, 50));

	InteractionPopupComponent = CreateDefaultSubobject<UWidgetComponent>("InteractionPopup");
	check(InteractionPopupComponent);
	InteractionPopupComponent->SetupAttachment(SceneRoot);
	InteractionPopupComponent->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionPopupComponent->SetWidgetClass(UInteractionPopup::StaticClass());
	InteractionPopupComponent->SetRelativeLocation(FVector(0, 0, 100));
	ToggleInteractionPopup(false);

	Tags.Add("Interactable" );
}

void AInteractable::ToggleInteractionPopup(bool show)
{
	UE_LOG(LogTemp, Warning, TEXT("Menu %d for %s"), show, *GetActorLabel());
	InteractionPopupComponent->SetHiddenInGame(!show);
}

void AInteractable::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Option executed: %s"), *InteractionOptions[CurrentOptionIndex]);
}

void AInteractable::CycleOptions(int32 nextIndex)
{
	CurrentOptionIndex = FMath::Clamp(CurrentOptionIndex + nextIndex, 0, InteractionOptions.Num() - 1);
	//UE_LOG(LogTemp, Warning, TEXT("Selected option: %s"), *InteractionOptions[CurrentOptionIndex]);
	InteractionPopup->SelectInteractionOption(CurrentOptionIndex);
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	InteractionPopup = CastChecked<UInteractionPopup, UUserWidget>(InteractionPopupComponent->GetUserWidgetObject());
	InteractionPopup->SetupPopup(InteractableName, InteractionOptions);
}

