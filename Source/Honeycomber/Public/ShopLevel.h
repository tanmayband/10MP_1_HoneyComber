// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Utils/Structs.h"
#include "ShopLevel.generated.h"

class AVisitorManager;
class UDataTable;

UCLASS()
class HONEYCOMBER_API AShopLevel : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<FVisitorData> VisitorList;
	/*UPROPERTY(EditDefaultsOnly)
		TArray<float> VisitorDelays*/;
	UPROPERTY(EditDefaultsOnly)
		AVisitorManager* VisitorManager;
	uint8 CurrentVisitorIndex = -1;

	void NextVisitor();
};
