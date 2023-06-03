// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopLevel.h"
#include "Actors/VisitorManager.h"
#include "Engine/DirectionalLight.h"
#include "Widgets/DayCheckpoint.h"
#include "Kismet/GameplayStatics.h"

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

	DayCheckpointWidget = CreateWidget<UDayCheckpoint>(UGameplayStatics::GetPlayerController(GetWorld(), 0), DayCheckpointWidgetClass);
	DayCheckpointWidget->AddToViewport();
	DayCheckpointWidget->SetupCheckpoint(1);
	DayCheckpointWidget->OnDayAnimDoneDelegate.BindLambda([&](bool isStartDay)
	{
		if (isStartDay)
		{
			NextVisitor();
		}
	});

	FTimerHandle fth;
	GetWorldTimerManager().SetTimer(fth, [&] {DayCheckpointWidget->StartDayAnim(); }, 2, false);
	
}

void AShopLevel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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
	//PauseDay = false;
	if (++CurrentVisitorIndex < VisitorList.Num())
	{
		// go to next visitor after a delay
		VisitorManager->SetupNewVisitor(VisitorList[CurrentVisitorIndex]);
		//PauseDay = true;
	}
}
