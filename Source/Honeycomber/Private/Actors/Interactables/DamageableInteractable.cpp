// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/DamageableInteractable.h"
#include "Components/WidgetComponent.h"
#include "Widgets/StateDisplay.h"
#include "Subsystems/MoneyFlowSubsystem.h"
#include "Widgets/InteractionPopup.h"

ADamageableInteractable::ADamageableInteractable()
{
	HealthDisplayComponent = CreateDefaultSubobject<UWidgetComponent>("HealthDisplay");
	check(HealthDisplayComponent);
	HealthDisplayComponent->SetupAttachment(SceneRoot);
	HealthDisplayComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthDisplayComponent->SetHiddenInGame(true);
}

void ADamageableInteractable::ToggleInteractionPopup(bool show)
{
	Super::ToggleInteractionPopup(show);
	HealthDisplayComponent->SetHiddenInGame(!show);
}

void ADamageableInteractable::SingleDamage(uint8 damageAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - damageAmount, 0, MaxHealth);
	UpdateHealthDisplay();
	ToggleHealOptionShow(true);

	if (CurrentHealth <= 0)
		DoDestroy();

	ProcessDamage();
}

void ADamageableInteractable::StartContinuousDamage(uint8 eachDamageAmount, float damageAtInterval)
{
	StopContinuousDamage();

	FTimerDelegate DamageDelegate = FTimerDelegate::CreateUObject(this, &ADamageableInteractable::SingleDamage, eachDamageAmount);
	GetWorldTimerManager().SetTimer(OngoingDamageHandle, DamageDelegate, damageAtInterval, true);
}

void ADamageableInteractable::HealDamage()
{
	UMoneyFlowSubsystem* moneySubsystem = GetGameInstance()->GetSubsystem<UMoneyFlowSubsystem>();
	if(moneySubsystem->MoneyRequested(GetHealCost()))
	{
		CurrentHealth = FMath::Clamp(CurrentHealth + OneHealAmount, 0, MaxHealth);
		UpdateHealthDisplay();

		if (CurrentHealth >= MaxHealth)
		{
			ToggleHealOptionShow(false);
			StopContinuousDamage();
		}

		ProcessHeal();
	}
}

void ADamageableInteractable::BeginPlay()
{
	Super::BeginPlay();

	HealthDisplay = CastChecked<UStateDisplay, UUserWidget>(HealthDisplayComponent->GetUserWidgetObject());
	UpdateHealthDisplay();
	UMoneyFlowSubsystem* moneySubsystem = GetGameInstance()->GetSubsystem<UMoneyFlowSubsystem>();
	moneySubsystem->OnMoneyChangedDelegate.AddUObject(this, &ADamageableInteractable::ProcessMoneyChange);

}

void ADamageableInteractable::InteractOption(uint8 index)
{
	if (InteractionOptions[index].OptionText.Compare(HealOptionText) == 0)
	{
		HealDamage();
	}
}

void ADamageableInteractable::ProcessDamage()
{
}

void ADamageableInteractable::ProcessHeal()
{
}

void ADamageableInteractable::ProcessDestroy()
{
}

uint32 ADamageableInteractable::GetHealCost()
{
	uint8 actualHealAmount = FMath::Min<uint8>(OneHealAmount, MaxHealth - CurrentHealth);
	uint32 healCost = actualHealAmount * OneHealCost;
	return healCost;
}

void ADamageableInteractable::UpdateHealthDisplay()
{
	HealthDisplay->SetupState("Health:", FString::FromInt(CurrentHealth));
	float isBad = CurrentHealth < (MaxHealth / 2);
	HealthDisplay->SetBGColour(isBad ? FLinearColor(0.6, 0.1, 0, 0.5) : FLinearColor(0.1, 0.6, 0, 0.5));
}

void ADamageableInteractable::ToggleHealOptionShow(bool show)
{
	int8 healOptionIndex = InteractionOptions.IndexOfByPredicate([this](FInteractionOptionEnabled optionData) {return optionData.OptionText.Compare(HealOptionText) == 0; });

	if (healOptionIndex >= 0)
	{
		InteractionOptions.RemoveAt(healOptionIndex);
	}

	if (show)
	{
		UMoneyFlowSubsystem* moneySubsystem = GetGameInstance()->GetSubsystem<UMoneyFlowSubsystem>();
		bool isHealPossible = moneySubsystem->IsMoneyAvailable(GetHealCost());
		InteractionOptions.Add(FInteractionOptionEnabled(HealOptionText, isHealPossible));
	}

	InteractionPopup->SetupPopupOptions(InteractionOptions);
}

void ADamageableInteractable::ToggleHealOptionEnabled(bool enable)
{
	uint8 healOptionIndex = InteractionOptions.IndexOfByPredicate([this](FInteractionOptionEnabled optionData) {return optionData.OptionText.Compare(HealOptionText); });
	if (healOptionIndex >= 0)
	{
		InteractionPopup->ToggleOptionEnabled(healOptionIndex, enable);
	}
}

void ADamageableInteractable::ProcessMoneyChange(uint32 newMoney)
{
	UMoneyFlowSubsystem* moneySubsystem = GetGameInstance()->GetSubsystem<UMoneyFlowSubsystem>();
	bool isHealPossible = moneySubsystem->IsMoneyAvailable(GetHealCost());
	ToggleHealOptionEnabled(isHealPossible);
}

void ADamageableInteractable::StopContinuousDamage()
{
	if (OngoingDamageHandle.IsValid())
		GetWorldTimerManager().ClearTimer(OngoingDamageHandle);
}

void ADamageableInteractable::DoDestroy()
{
	StopContinuousDamage();
	ProcessDestroy();
}
