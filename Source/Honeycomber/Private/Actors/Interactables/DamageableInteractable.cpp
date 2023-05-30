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
