// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/MoneyFlowSubsystem.h"

bool UMoneyFlowSubsystem::MoneyRequested(uint32 amount)
{
	bool isAvailable = IsMoneyAvailable(amount);
	if (isAvailable)
	{
		CurrentMoney -= amount;
		MoneyChanged();
	}
	return isAvailable;
}

void UMoneyFlowSubsystem::MoneyAdded(uint32 amount)
{
	CurrentMoney += amount;
	MoneyChanged();
}

bool UMoneyFlowSubsystem::IsMoneyAvailable(uint32 amount)
{
	return amount <= CurrentMoney;
}

void UMoneyFlowSubsystem::MoneyChanged()
{
	OnMoneyChangedDelegate.Broadcast(CurrentMoney);
}
