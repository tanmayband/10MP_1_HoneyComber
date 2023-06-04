// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Misc/BeeFrame.h"
#include "Components/WidgetComponent.h"
#include "Widgets/InteractionPopup.h"

// Sets default values
ABeeFrame::ABeeFrame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	check(SceneRoot);
	SetRootComponent(SceneRoot);

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>("FrameMesh");
	check(FrameMesh);
	FrameMesh->SetupAttachment(SceneRoot);

	FrameRemovePopupComponent = CreateDefaultSubobject<UWidgetComponent>("FrameRemovePopupComponent");
	check(FrameRemovePopupComponent);
	FrameRemovePopupComponent->SetupAttachment(SceneRoot);
	FrameRemovePopupComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void ABeeFrame::SetupFrame(uint8 index)
{
	FrameIndex = index;
}

// Called when the game starts or when spawned
void ABeeFrame::BeginPlay()
{
	Super::BeginPlay();
	
	FrameRemovePopup = CastChecked<UInteractionPopup, UUserWidget>(FrameRemovePopupComponent->GetUserWidgetObject());
	FrameRemovePopup->SetupPopup("Frame", {
		FInteractionOptionEnabled("Remove (+10 Disturbance)", true)
	}, PopupPivot);
	FrameRemovePopup->OnOptionSelectedDelegate.BindUObject(this, &ABeeFrame::FrameInteract);
}

// Called every frame
void ABeeFrame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABeeFrame::OnConstruction(const FTransform& Transform)
{
	FrameRemovePopupComponent->SetPivot(PopupPivot);
}

void ABeeFrame::FrameInteract(uint8 optionIndex)
{
	OnFrameRemovedEvent.ExecuteIfBound(FrameIndex);
}

