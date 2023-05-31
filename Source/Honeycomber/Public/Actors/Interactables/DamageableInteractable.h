// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactables/Interactable.h"
#include "DamageableInteractable.generated.h"

class UStateDisplay;

UCLASS()
class HONEYCOMBER_API ADamageableInteractable : public AInteractable
{
	GENERATED_BODY()

public:
	ADamageableInteractable();
	virtual void ToggleInteractionPopup(bool show) override;
	UFUNCTION(BlueprintCallable)
	void SingleDamage(uint8 damageAmount);
	UFUNCTION(BlueprintCallable)
	void StartContinuousDamage(uint8 eachDamageAmount, float damageAtInterval);
	UFUNCTION(BlueprintCallable)
	void HealDamage();

protected:
	UPROPERTY(EditAnywhere)
		uint8 MaxHealth = 100;
	UPROPERTY(EditAnywhere)
		uint8 CurrentHealth = 100;

	virtual void BeginPlay() override;
	virtual void InteractOption(uint8 index) override;
	virtual void ProcessDamage();
	virtual void ProcessHeal();
	virtual void ProcessDestroy();

private:
	// for continuous damage
	uint8 EachDamage;
	float DamageInterval;
	FTimerHandle OngoingDamageHandle;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* HealthDisplayComponent;
	UStateDisplay* HealthDisplay;

	// healing
	UPROPERTY(EditAnywhere)
		uint8 OneHealCost = 1;
	UPROPERTY(EditAnywhere)
		uint8 OneHealAmount = 5;
	UPROPERTY(EditAnywhere)
		FString HealOptionText = "Fix damage";

	uint32 GetHealCost();
	void UpdateHealthDisplay();
	void ToggleHealOptionShow(bool show);
	void ToggleHealOptionEnabled(bool enable);
	void ProcessMoneyChange(uint32 newMoney);
	void StopContinuousDamage();
	void DoDestroy();
};
