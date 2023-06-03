// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MoneyFlowSubsystem.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FMoneyChangedSignature, uint32 currentMoney);

UCLASS()
class HONEYCOMBER_API UMoneyFlowSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	bool MoneyRequested(uint32 amount);
	void MoneyAdded(uint32 amount);
	bool IsMoneyAvailable(uint32 amount);
	uint32 GetCurrentMoney() { return CurrentMoney; };
	FMoneyChangedSignature OnMoneyChangedDelegate;

private:
	uint32 CurrentMoney;
	void MoneyChanged();
};
