// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/Interactable.h"
#include "Utils/Enums.h"
#include "Beehive.generated.h"

class UStaticMeshComponent;
class UStateDisplay;

DECLARE_DELEGATE_OneParam(FExtractedResourceSignature, EResourceType resourceType)

UCLASS()
class HONEYCOMBER_API ABeehive : public AInteractable
{
	GENERATED_BODY()

public:
	ABeehive();
	void OnConstruction(const FTransform& Transform);
	void Tick(float DeltaSeconds);

	//UFUNCTION(BlueprintCallable)
	int32 GetCurrentHoneyJars();
	void InteractOption(int32 index) override;
	void DisableExtraction(EResourceType resourceType);

	FExtractedResourceSignature ExtractedResourceDelegate;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BeehiveMesh;
	UPROPERTY(EditAnywhere)
		float HoneyJarRatePerBee = 0.001f;		// number of jars per bee per second
	UPROPERTY(EditAnywhere)
		int32 NumBees = 50;
	UPROPERTY(EditAnywhere)
		int32 MaxHoneyJars = 10;
	float CurrentHoneyJars;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UStateDisplay> StateDisplayClass;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* HoneyDisplayComponent;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* WaxDisplayComponent;

	UStateDisplay* HoneyDisplay;
	UStateDisplay* WaxDisplay;

};
