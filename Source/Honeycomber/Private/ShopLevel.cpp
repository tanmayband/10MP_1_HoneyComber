// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopLevel.h"
#include "Actors/VisitorManager.h"
#include "Engine/DirectionalLight.h"

AShopLevel::AShopLevel()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShopLevel::BeginPlay()
{
	Super::BeginPlay();

	Daylight->SetActorRotation(FRotator(90, 0, 0));

	VisitorManager->SetupVisitorManager();
	VisitorManager->OnVisitorDoneDelegate.BindUObject(this, &AShopLevel::NextVisitor);
	NextVisitor();
}

void AShopLevel::Tick(float DeltaSeconds)
{
	if(!PauseDay)
	{
		DayProgress = FMath::Clamp(DayProgress + (DeltaSeconds * DaySpeed), 0, 1);
		Daylight->SetActorRotation(
			FRotator(FQuat::SlerpFullPath(FRotator(90, 0, 0).Quaternion(), FRotator(-180, 0, 0).Quaternion(), DayProgress))
		);
		if (DayProgress >= 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Day end"));
		}
	}
}

void AShopLevel::NextVisitor()
{
	PauseDay = false;
	if (++CurrentVisitorIndex < VisitorList.Num())
	{
		// go to next visitor after a delay
		VisitorManager->SetupNewVisitor(VisitorList[CurrentVisitorIndex]);
		PauseDay = true;
	}
}
