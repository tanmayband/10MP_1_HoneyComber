// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ComberCharacter.generated.h"

class UStaticMeshComponent;
class UInputMappingContext;
class UInputAction;
class AInteractable;

UCLASS()
class HONEYCOMBER_API AComberCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AComberCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ComberBody;
	UPROPERTY(EditDefaultsOnly)
		UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly)
		UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly)
		UInputAction* CycleOptionsAction;
	UPROPERTY(EditDefaultsOnly)
		UInputAction* SelectOptionAction;

	AInteractable* CurrentInteractable;

	void MoveComber(const FInputActionValue& Value);
	void CycleInteractionOptions(const FInputActionValue& Value);
	void HighlightInteractionOption(const FInputActionValue& Value);
	UFUNCTION()
		void ComberOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void ComberOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
