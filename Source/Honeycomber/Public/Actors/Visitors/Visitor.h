// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums.h"
#include "Visitor.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UStateDisplay;

UCLASS()
class HONEYCOMBER_API AVisitor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVisitor();
	void SetupVisitor(EVisitorype visitorType, FString visitorName);
	void ToggleStateDisplay(bool show);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisitorMesh;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* VisitorDisplayComponent;
	UStateDisplay* VisitorDisplay;
	
	FString VisitorName;
	EVisitorype VisitorType = EVisitorype::VISITOR;
};
