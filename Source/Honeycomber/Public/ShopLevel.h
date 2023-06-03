// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Utils/Structs.h"
#include "ShopLevel.generated.h"

class AVisitorManager;
class UDataTable;
class ADirectionalLight;
class UDayCheckpoint;

UCLASS()
class HONEYCOMBER_API AShopLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AShopLevel();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditDefaultsOnly)
		ADirectionalLight* Daylight;
	UPROPERTY(EditDefaultsOnly)
		TArray<FVisitorData> VisitorList;
	/*UPROPERTY(EditDefaultsOnly)
		TArray<float> VisitorDelays*/;
	UPROPERTY(EditDefaultsOnly)
		AVisitorManager* VisitorManager;
	uint8 CurrentVisitorIndex = -1;

	void NextVisitor();
	bool PauseDay = true;
	bool VisitorsStarted = false;
	UPROPERTY(EditDefaultsOnly)
		float DaySeconds = 60 * 2;
	float DayProgress = 0;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UDayCheckpoint> DayCheckpointWidgetClass;
	UDayCheckpoint* DayCheckpointWidget;
};
