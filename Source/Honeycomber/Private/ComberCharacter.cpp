// Fill out your copyright notice in the Description page of Project Settings.


#include "ComberCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/Interactables/Interactable.h"

// Sets default values
AComberCharacter::AComberCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneRoot = CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent());

	ComberBody = CreateDefaultSubobject<UStaticMeshComponent>("ComberBody");
	check(ComberBody);
	ComberBody->SetupAttachment(SceneRoot);
	bUseControllerRotationYaw = false;
	UCharacterMovementComponent* ComberMovement = GetCharacterMovement();
	ComberMovement->bOrientRotationToMovement = true;
	ComberMovement->RotationRate = FRotator(0, 720, 0);
}

// Called when the game starts or when spawned
void AComberCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get the player controller
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->SetShowMouseCursor(true);
		// Get the local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// Clear out existing mapping, and add our mapping
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &AComberCharacter::ComberOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddUniqueDynamic(this, &AComberCharacter::ComberOverlapEnd);
}

// Called to bind functionality to input
void AComberCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AComberCharacter::MoveComber);
		EnhancedInputComponent->BindAction(CycleOptionsAction, ETriggerEvent::Triggered, this, &AComberCharacter::CycleInteractionOptions);
		EnhancedInputComponent->BindAction(SelectOptionAction, ETriggerEvent::Triggered, this, &AComberCharacter::SelectInteractionOption);
	}
}

void AComberCharacter::MoveComber(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	
	const FRotator ControllerRotation = GetController()->GetControlRotation();
	const FRotator ControllerYawRotation(0, ControllerRotation.Yaw, 0);
	const FVector ControllerForwardDirection = FRotationMatrix(ControllerYawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ControllerForwardDirection, MoveVector.Y);

	const FVector ControllerRightDirection = FRotationMatrix(ControllerYawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ControllerRightDirection, MoveVector.X);
}

void AComberCharacter::CycleInteractionOptions(const FInputActionValue& Value)
{
	const float CycleDirection = Value.Get<float>();
	if (CurrentInteractable)
		CurrentInteractable->CycleOptions((int32)CycleDirection);
}

void AComberCharacter::SelectInteractionOption(const FInputActionValue& Value)
{
	if (CurrentInteractable)
		CurrentInteractable->Interact();
}

void AComberCharacter::ComberOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Interactable"))
	{
		if (CurrentInteractable)
		{
			CurrentInteractable->ToggleInteractionPopup(false);
		}
		CurrentInteractable = CastChecked<AInteractable, AActor>(OtherActor);
		CurrentInteractable->ToggleInteractionPopup(true);
	}
}

void AComberCharacter::ComberOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Interactable"))
	{
		if (OtherActor == CurrentInteractable)
		{
			CurrentInteractable->ToggleInteractionPopup(false);
			CurrentInteractable = nullptr;
		}
	}
}

