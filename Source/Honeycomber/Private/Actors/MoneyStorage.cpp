// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MoneyStorage.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/StateDisplay.h"

// Sets default values
AMoneyStorage::AMoneyStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	check(SceneRoot);
	SetRootComponent(SceneRoot);

	MoneyDisplayComponent = CreateDefaultSubobject<UWidgetComponent>("MoneyDisplay");
	check(MoneyDisplayComponent);
	MoneyDisplayComponent->SetupAttachment(SceneRoot);
	MoneyDisplayComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void AMoneyStorage::AddMoney(uint8 newMoney)
{
	MoneyAmount += newMoney;
	MoneyDisplay->UpdateState(FString::FromInt(MoneyAmount));
}

// Called when the game starts or when spawned
void AMoneyStorage::BeginPlay()
{
	Super::BeginPlay();
	MoneyDisplay = CastChecked<UStateDisplay, UUserWidget>(MoneyDisplayComponent->GetUserWidgetObject());
	MoneyDisplay->SetupState("Money:", "0");
}

