// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ComberCharacter.generated.h"

class UStaticMeshComponent;
class UInputMappingContext;
class UInputAction;

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ComberBody;
	UPROPERTY(EditDefaultsOnly)
		UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly)
		UInputAction* MoveAction;

	void MoveComber(const FInputActionValue& Value);
};
