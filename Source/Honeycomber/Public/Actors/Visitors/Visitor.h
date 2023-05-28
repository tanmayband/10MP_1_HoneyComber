// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums.h"
#include "Visitor.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UDialogueWidget;
class UDataTable;

UCLASS()
class HONEYCOMBER_API AVisitor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVisitor();
	UFUNCTION(BlueprintCallable)
		void SetupVisitor(EVisitorType visitorType, FString visitorName);
	UFUNCTION(BlueprintCallable)
		void UpdateOptions(TArray<FString> responseOptions);
	UFUNCTION(BlueprintPure)
		TArray<FString> GetOptions();
	UFUNCTION(BlueprintCallable)
		void ToggleDialogueDisplay(bool show);
	UFUNCTION(BlueprintCallable)
		virtual void ProcessOption(uint8 optionIndex);
	
	UDataTable* StartTalking();
	void DisplayDialogueLine(FString dialogueLine);
	void StopTalking();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisitorMesh;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* VisitorDialogueComponent;
	UDialogueWidget* VisitorDialogue;

	//UPROPERTY(EditAnywhere)
	UDataTable* VisitorDialogueTable;
	
	FString VisitorName;
	EVisitorType VisitorType = EVisitorType::VISITOR;
	TArray<FString> ResponseOptions = {"Yes, here you go!", "Sorry, we're out"};
};
