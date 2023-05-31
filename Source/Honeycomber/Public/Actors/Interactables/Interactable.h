// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Structs.h"
#include "Interactable.generated.h"

class USceneComponent;
class UBoxComponent;
class UWidgetComponent;
class UInteractionPopup;

UCLASS()
class HONEYCOMBER_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();
	void OnConstruction(const FTransform& Transform);

	virtual void ToggleInteractionPopup(bool show);
	void Interact();
	UFUNCTION()
		virtual void InteractOption(uint8 index);
	void CycleOptions(uint8 nextIndex);
	void SetInteractableName(FString newName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true))
		FVector PopupLocation = FVector(0, 0, 50);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere)
		UBoxComponent* InteractionArea;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* InteractionPopupComponent;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UInteractionPopup> InteractionPopupClass;
	UInteractionPopup* InteractionPopup;

	UPROPERTY(EditAnywhere)
		FString InteractableName = "SomeInteractable";
	UPROPERTY(EditAnywhere)
		TArray<FInteractionOptionEnabled> InteractionOptions;
	uint8 CurrentOptionIndex = 0;
	UPROPERTY(EditAnywhere)
		FVector2D PopupPivot = FVector2D(0.5,0.5);
};
