// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactables/DamageableInteractable.h"
#include "Components/WidgetComponent.h"
#include "Widgets/StateDisplay.h"

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
	ProcessDamage();

	if (CurrentHealth <= 0)
		DoDestroy();
}

void ADamageableInteractable::StartContinuousDamage(uint8 eachDamageAmount, float damageAtInterval)
{
	StopContinuousDamage();

	FTimerDelegate DamageDelegate = FTimerDelegate::CreateUObject(this, &ADamageableInteractable::SingleDamage, eachDamageAmount);
	GetWorldTimerManager().SetTimer(OngoingDamageHandle, DamageDelegate, damageAtInterval, true);
}

void ADamageableInteractable::HealDamage(uint8 healAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + healAmount, 0, MaxHealth);
	UpdateHealthDisplay();
	ProcessHeal();

	if (CurrentHealth >= MaxHealth)
		StopContinuousDamage();
}

void ADamageableInteractable::BeginPlay()
{
	Super::BeginPlay();

	HealthDisplay = CastChecked<UStateDisplay, UUserWidget>(HealthDisplayComponent->GetUserWidgetObject());
	UpdateHealthDisplay();
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

void ADamageableInteractable::UpdateHealthDisplay()
{
	HealthDisplay->SetupState("Health:", FString::FromInt(CurrentHealth));
	float isBad = CurrentHealth < (MaxHealth / 2);
	HealthDisplay->SetBGColour(isBad ? FLinearColor(0.6, 0.1, 0, 0.5) : FLinearColor(0.1, 0.6, 0, 0.5));
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
