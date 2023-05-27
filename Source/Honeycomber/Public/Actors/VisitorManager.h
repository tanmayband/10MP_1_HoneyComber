// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums.h"
#include "VisitorManager.generated.h"

class USplineComponent;
class AVisitor;
class ADesk;
class AResourceManager;
class ADialogueManager;
class UDataTable;

UCLASS()
class HONEYCOMBER_API AVisitorManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVisitorManager();
	void Tick(float DeltaSeconds);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere)
		USplineComponent* VisitorSpline;

	UPROPERTY(EditAnywhere)
		ADesk* SaleDesk;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AVisitor> VisitorClass;
	UPROPERTY(EditAnywhere)
		AResourceManager* ResourceManager;
	UPROPERTY(EditAnywhere)
		ADialogueManager* DialogueManager;
	
	AVisitor* CurrentVisitor;
	float VisitorSplineDuration = 5.0f;
	float VisitorSplineLength;
	float CurrentVisitorSplineProgress;
	int8 CurrentVisitorSplineDirection = 1;
	bool CurrentVisitorSplineMovementDone;
	UPROPERTY(EditAnywhere)
		UDataTable* CurrentVisitorDialogueTable;

	void SpawnVisitor();
	void ResourcesUpdated(EResourceType resourceType, int32 numResources);
	void ResponsePicked(int32 optionIndex);
};
