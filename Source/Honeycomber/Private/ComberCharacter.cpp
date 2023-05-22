// Fill out your copyright notice in the Description page of Project Settings.


#include "ComberCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AComberCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get the player controller
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Get the local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// Clear out existing mapping, and add our mapping
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

// Called every frame
void AComberCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AComberCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked< UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AComberCharacter::MoveComber);
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

