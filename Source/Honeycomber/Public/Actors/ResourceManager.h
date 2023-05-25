// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums.h"
#include "ResourceManager.generated.h"

class ABeehive;
class AResourceStorage;

UCLASS()
class HONEYCOMBER_API AResourceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TArray<ABeehive*> Beehives;
	UPROPERTY(EditAnywhere)
		TArray<AResourceStorage*> HoneyStores;
	UPROPERTY(EditAnywhere)
		TArray<AResourceStorage*> WaxStores;

	int32 TryAddingResources(EResourceType resourceType, int32 numResources);
};
