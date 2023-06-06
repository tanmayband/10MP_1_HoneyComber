// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Structs.h"
#include "BeeFrame.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UInteractionPopup;

DECLARE_DELEGATE_OneParam(FFrameRemovedSignature, uint8 index);

UCLASS()
class HONEYCOMBER_API ABeeFrame : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeeFrame();
	void SetupFrame(uint8 index);
	void TogglePopup(bool show);
	FFrameRemovedSignature OnFrameRemovedEvent;
	bool isEnabled = true;
	FBeeFrameData GetFrameData() { return FrameData; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnConstruction(const FTransform& Transform);

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* FrameMesh;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* FrameRemovePopupComponent;
	UInteractionPopup* FrameRemovePopup;
	UPROPERTY(EditAnywhere)
		FVector2D PopupPivot = FVector2D(0, 0.5);

	uint8 FrameIndex;
	FBeeFrameData FrameData;
	UFUNCTION()
		void FrameInteract(uint8 optionIndex);
};
