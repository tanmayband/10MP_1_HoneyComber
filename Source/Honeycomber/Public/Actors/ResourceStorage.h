// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums.h"
#include "ResourceStorage.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UStateDisplay;

UCLASS()
class HONEYCOMBER_API AResourceStorage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceStorage();
	void OnConstruction(const FTransform& Transform);
	void SetupResourceStorage(EResourceType resourceType, int32 maxAmount, int32 currentAmount = 0);
	void ModifyResourceAmount(int32 amountDelta);
	int32 GetAvailableResources();
	int32 GetAvailableSpace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		EResourceType ResourceType = EResourceType::NONE;
	FString ResourceName;
	int32 CurrentResourceAmount;
	UPROPERTY(EditAnywhere)
		int32 MaxResourceAmount = 10;

	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StorageMesh;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* ResourceDisplayComponent;
	UStateDisplay* ResourceDisplay;
};
