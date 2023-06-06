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
class UFrameInventory;

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
		TArray<UDataTable*> DaysVisitorTables;
	TArray<FVisitorData*> TodayVisitorList;
	/*UPROPERTY(EditDefaultsOnly)
		TArray<float> VisitorDelays*/;
	UPROPERTY(EditDefaultsOnly)
		AVisitorManager* VisitorManager;
	uint8 CurrentVisitorIndex;

	void ResetDay();
	void SetupTodaysVisitors();
	void NextVisitor();
	bool PauseDay = true;
	bool VisitorsStarted = false;
	UPROPERTY(EditDefaultsOnly)
		float DaySeconds = 60 * 2;
	float DayProgress = 0;
	uint8 DayNum = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UDayCheckpoint> DayCheckpointWidgetClass;
	UDayCheckpoint* DayCheckpointWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UFrameInventory> FrameInventoryClass;
};
