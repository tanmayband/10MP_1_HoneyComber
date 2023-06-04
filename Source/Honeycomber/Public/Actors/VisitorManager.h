// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Structs.h"
#include "VisitorManager.generated.h"

class USplineComponent;
class AVisitor;
class ADesk;
//class AResourceManager;
class ADialogueManager;
class UDataTable;

DECLARE_DELEGATE(FVisitorDoneSignature);

UCLASS()
class HONEYCOMBER_API AVisitorManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVisitorManager();
	void Tick(float DeltaSeconds);
	void SetupVisitorManager();
	void SetupNewVisitor(FVisitorData visitorData);
	FVisitorDoneSignature OnVisitorDoneDelegate;

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
		ADialogueManager* DialogueManager;
	
	AVisitor* CurrentVisitor;
	float VisitorSplineDuration = 5.0f;
	float VisitorSplineLength;
	float CurrentVisitorSplineProgress;
	int8 CurrentVisitorSplineDirection = 1;
	bool CurrentVisitorSplineMovementDone;

	void SpawnVisitor(FVisitorData visitorData);
	void ResourcesUpdated(EResourceType resourceType, uint8 numResources);
	void DisplayDialogue(FString dialogueLine);
	void ResponsePicked(uint8 optionIndex);
	void DoneTalking();
};
