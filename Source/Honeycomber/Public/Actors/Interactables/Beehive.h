// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/DamageableInteractable.h"
#include "Utils/Enums.h"
#include "Beehive.generated.h"

class UStaticMeshComponent;

DECLARE_DELEGATE_RetVal_TwoParams(uint8, FExtractedResourceSignature, EResourceType resourceType, int16 resourceAmount)

UCLASS()
class HONEYCOMBER_API ABeehive : public ADamageableInteractable
{
	GENERATED_BODY()

public:
	ABeehive();
	void OnConstruction(const FTransform& Transform);
	void Tick(float DeltaSeconds);

	//UFUNCTION(BlueprintCallable)
	uint8 GetCurrentHoneyJars();
	void InteractOption(uint8 index) override;
	void DisableExtraction(EResourceType resourceType);
	void UpdateBees();
	uint8 GetBees() { return NumBees; };

	FExtractedResourceSignature ExtractedResourceDelegate;

protected:
	virtual void BeginPlay() override;
	virtual void ProcessHeal() override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BeehiveMesh;

	/***** STATS *****/

	UPROPERTY(EditAnywhere)
		uint8 NumBees = 200;

	UPROPERTY(EditAnywhere)
		float HoneyJarRatePerBee = 0.005f;		// number of jars per bee per unit time
	UPROPERTY(EditAnywhere)
		uint8 MaxHoneyJars = 10;
	float CurrentHoneyJars;
	UPROPERTY(EditAnywhere)
		uint8 HoneyExtractAmount = 1;

	UPROPERTY(EditAnywhere)
		float WaxJarRatePerBee = 0.05f;		// number of jars per bee per unit time
	UPROPERTY(EditAnywhere)
		uint8 MaxWaxJars = 5;
	float CurrentWaxJars;
	UPROPERTY(EditAnywhere)
		uint8 WaxExtractAmount = 1;

	uint8 Disturbance;					// higher the more frequenct you extract; has cooldown
	uint8 Damage;						// internal damage (wood rot, mites, infection)
	UPROPERTY(EditAnywhere)
		float DisturbanceMultiplier = 0.2;
	UPROPERTY(EditAnywhere)
		float HoneyGenerationMultiplier = 0.01;

	UPROPERTY(EditAnywhere)
		uint8 NumBeesRequiringOneJar = 200;		// should be <= than starter numBees
	/*****************/

	UPROPERTY(EditAnywhere)
		TSubclassOf<UStateDisplay> StateDisplayClass;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* HoneyDisplayComponent;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* WaxDisplayComponent;

	UStateDisplay* HoneyDisplay;
	UStateDisplay* WaxDisplay;

	//void CalculateHealth();

};
