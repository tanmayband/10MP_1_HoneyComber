// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	void ToggleInteractionPopup(bool show);
	void Interact();
	void CycleOptions(int32 nextIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere)
		UBoxComponent* InteractionArea;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* InteractionPopupComponent;

	UInteractionPopup* InteractionPopup;

	UPROPERTY(EditAnywhere)
		FString InteractableName = "SomeInteractable";
	UPROPERTY(EditAnywhere)
		TArray<FString> InteractionOptions;
	int32 CurrentOptionIndex = 0;
};
