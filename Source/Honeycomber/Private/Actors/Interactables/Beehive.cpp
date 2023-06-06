// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/Beehive.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Widgets/InteractionPopup.h"
#include "Components/WidgetComponent.h"
#include "Widgets/StateDisplay.h"
#include "Subsystems/ResourceManagerSubsystem.h"
#include "Subsystems/BeehiveManagerSubsystem.h"
#include "Subsystems/InventorySubsystem.h"
#include "Components/ChildActorComponent.h"
#include "Actors/Misc/BeeFrame.h"

ABeehive::ABeehive()
{
	PrimaryActorTick.bCanEverTick = true;
	BeehiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeehiveMesh"));
	check(BeehiveMesh)
	BeehiveMesh->SetupAttachment(SceneRoot);

	for (uint8 iFrame = 0; iFrame < 4; iFrame++)
	{
		UChildActorComponent* frameActor = CreateDefaultSubobject<UChildActorComponent>(*FString::Printf(TEXT("BeeFrame_%d"), iFrame));
		frameActor->SetupAttachment(BeehiveMesh);
		BeeFrameComponents.Add(frameActor);
	}

	FrameCamera = CreateDefaultSubobject<UCameraComponent>("FrameCamera");
	check(FrameCamera);
	FrameCamera->SetupAttachment(SceneRoot);

	ExitInspectPopupComponent = CreateDefaultSubobject<UWidgetComponent>("ExitInspectPopup");
	check(ExitInspectPopupComponent);
	ExitInspectPopupComponent->SetupAttachment(SceneRoot);
	ExitInspectPopupComponent->SetWidgetSpace(EWidgetSpace::Screen);
	ExitInspectPopupComponent->SetHiddenInGame(true);

	HoneyDisplayComponent = CreateDefaultSubobject<UWidgetComponent>("HoneyDisplay");
	check(HoneyDisplayComponent);
	HoneyDisplayComponent->SetupAttachment(SceneRoot);
	HoneyDisplayComponent->SetWidgetSpace(EWidgetSpace::Screen);

	WaxDisplayComponent = CreateDefaultSubobject<UWidgetComponent>("WaxDisplay");
	check(WaxDisplayComponent);
	WaxDisplayComponent->SetupAttachment(SceneRoot);
	WaxDisplayComponent->SetWidgetSpace(EWidgetSpace::Screen);

	InteractionOptions = {
		FInteractionOptionEnabled("Inspect", true)
	};
}

void ABeehive::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	ExitInspectPopupComponent->SetWidgetClass(InteractionPopupClass);
	ExitInspectPopupComponent->SetPivot(FVector2D(0, 0.5));
	
	HoneyDisplayComponent->SetWidgetClass(StateDisplayClass);
	WaxDisplayComponent->SetWidgetClass(StateDisplayClass);
	for (UChildActorComponent* beeFrameActor : BeeFrameComponents)
	{
		beeFrameActor->SetChildActorClass(BeeFrameClass);
	}
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
	UResourceManagerSubsystem* resourceSubsystem = GetGameInstance()->GetSubsystem<UResourceManagerSubsystem>();
	switch (index)
	{
	case 0:
	{
		GoToFrameCamera();
		//if (CurrentHoneyJars > 1)
		//{
		//	CurrentHoneyJars -= resourceSubsystem->TryAddingResources(EResourceType::HONEY, FMath::Min(HoneyExtractAmount, CurrentHoneyJars));
		//	//CurrentHoneyJars -= ExtractedResourceDelegate.Execute(EResourceType::HONEY, FMath::Min(HoneyExtractAmount, CurrentHoneyJars));
		//	
		//}
		//break;
	}
	case 1:
	{
		if (CurrentWaxJars > 1)
		{
			CurrentWaxJars -= resourceSubsystem->TryAddingResources(EResourceType::WAX, FMath::Min(WaxExtractAmount, CurrentWaxJars));
			//CurrentWaxJars -= ExtractedResourceDelegate.Execute(EResourceType::WAX, FMath::Min(WaxExtractAmount, CurrentWaxJars));
			
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
	uint8 possibleBees = (int)CurrentHoneyJars * NumBeesRequiringOneJar;
	uint8 survivingBees = FMath::Min(NumBees, possibleBees);
	
	// TODO: tell some widget how many bees died (NumBees - survivingBees)

	// update current bees
	NumBees = survivingBees;
}

void ABeehive::BeginPlay()
{
	Super::BeginPlay();

	ExitInspectPopup = CastChecked<UInteractionPopup, UUserWidget>(ExitInspectPopupComponent->GetUserWidgetObject());
	ExitInspectPopup->SetupPopup(InteractableName, {
		FInteractionOptionEnabled("Back", true)
	}, FVector2D(0,0.5));
	ExitInspectPopup->OnOptionSelectedDelegate.BindLambda([&](uint8 optionIndex)
	{
		GoToMainCamera();
	});

	HoneyDisplay = CastChecked<UStateDisplay, UUserWidget>(HoneyDisplayComponent->GetUserWidgetObject());
	WaxDisplay = CastChecked<UStateDisplay, UUserWidget>(WaxDisplayComponent->GetUserWidgetObject());
	HoneyDisplay->SetupState("Honey jars:", "0");
	WaxDisplay->SetupState("Wax jars:", "0");

	uint8 iBeeFrame(0);
	BeeFrames.Empty();
	for (UChildActorComponent* beeFrameActor : BeeFrameComponents)
	{
		ABeeFrame* beeFrame = CastChecked<ABeeFrame>(beeFrameActor->GetChildActor());
		FBeeFrameData beeFrameData;
		beeFrameData.HoneyFill = FMath::RandRange(0, 100);
		beeFrame->SetupFrame(iBeeFrame, beeFrameData);
		BeeFrames.Add(beeFrame);
		beeFrame->OnFrameRemovedEvent.BindUObject(this, &ABeehive::RemoveFrame);
		iBeeFrame++;
	}

	StartContinuousDamage(5, 20);

	UBeehiveManagerSubsystem* beehiveSubsystem = GetGameInstance()->GetSubsystem<UBeehiveManagerSubsystem>();
	beehiveSubsystem->RegisterBeehive(this);
}

void ABeehive::ProcessHeal()
{
	if (CurrentHealth >= MaxHealth)
	{
		// restart damage when reached max health
		StartContinuousDamage(5, 20);
	}
}

void ABeehive::GoToFrameCamera()
{
	InteractionPopupComponent->SetHiddenInGame(true);
	GetWorld()->GetFirstPlayerController()->SetIgnoreMoveInput(true);
	GlobalCamera = GetWorld()->GetFirstPlayerController()->GetViewTarget();
	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
	FTimerHandle blendHandle;
	GetWorldTimerManager().SetTimer(blendHandle, [&] {
		ExitInspectPopupComponent->SetHiddenInGame(false);
		for (ABeeFrame* beeFrame : BeeFrames)
		{
			beeFrame->TogglePopup(true);
		}
		UInventorySubsystem* inventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
		inventorySubsystem->SetFrameAcceptor(this);
	},
	CameraBlendTime, false);
}

void ABeehive::GoToMainCamera()
{
	UInventorySubsystem* inventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	inventorySubsystem->SetFrameAcceptor(nullptr);
	ExitInspectPopupComponent->SetHiddenInGame(true);
	for (ABeeFrame* beeFrame : BeeFrames)
	{
		beeFrame->TogglePopup(false);
	}
	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(GlobalCamera, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
	GlobalCamera = nullptr;
	FTimerHandle blendHandle;
	GetWorldTimerManager().SetTimer(blendHandle, [&] {
		InteractionPopupComponent->SetHiddenInGame(false);
		GetWorld()->GetFirstPlayerController()->ResetIgnoreMoveInput();
		},
		CameraBlendTime, false);
}

EFrameAcceptorType ABeehive::GetAcceptorType()
{
	return EFrameAcceptorType::BEEHIVE;
}

bool ABeehive::AcceptFrame(FBeeFrameData frameData)
{
	bool isFrameAccepted(false);
	uint8 iFrame(0);
	while (!isFrameAccepted && iFrame < BeeFrames.Num())
	{
		isFrameAccepted = !BeeFrames[iFrame]->isEnabled;
		if(isFrameAccepted)
		{
			BeeFrames[iFrame]->SetupFrame(iFrame, frameData);
			BeeFrames[iFrame]->isEnabled = true;
			BeeFrames[iFrame]->SetActorHiddenInGame(false);
		}
		iFrame++;
	};
	return isFrameAccepted;
}

void ABeehive::RemoveFrame(uint8 frameIndex)
{
	UInventorySubsystem* inventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	if (inventorySubsystem->AddFrameToInventory(BeeFrames[frameIndex]->GetFrameData()))
	{
		BeeFrames[frameIndex]->isEnabled = false;
		BeeFrames[frameIndex]->SetActorHiddenInGame(true);
	}
}
