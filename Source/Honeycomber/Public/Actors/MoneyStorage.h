// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoneyStorage.generated.h"

class USceneComponent;
class UWidgetComponent;
class UStateDisplay;

UCLASS()
class HONEYCOMBER_API AMoneyStorage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoneyStorage();
	void UpdateMoneyDisplay(uint32 newMoney);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* MoneyDisplayComponent;
	UStateDisplay* MoneyDisplay;
};
