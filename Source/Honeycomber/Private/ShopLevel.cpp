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
			PauseDay = false;
		}
	});

	DayCheckpointWidget->StartDayAnim();
}

void AShopLevel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!PauseDay)
	{
		DayProgress = FMath::Clamp(DayProgress + (DeltaSeconds / DaySeconds), 0, 1);
		Daylight->SetActorRotation(
			FRotator(FQuat::SlerpFullPath(FRotator(10, 0, 0).Quaternion(), FRotator(-180, 0, 0).Quaternion(), DayProgress))
		);
		if (DayProgress >= 1)
		{
			PauseDay = true;
			UE_LOG(LogTemp, Warning, TEXT("Day end"));
			DayCheckpointWidget->EndDayAnim();
			DayProgress = 0;
		}
		else if (!VisitorsStarted && DayProgress >= 0.2)
		{
			VisitorsStarted = true;
			NextVisitor();
		}
	}
}

void AShopLevel::NextVisitor()
{
	PauseDay = false;
	if (++CurrentVisitorIndex < VisitorList.Num())
	{
		// go to next visitor after a delay
		FTimerHandle visitorHandle;
		GetWorldTimerManager().SetTimer(visitorHandle, [&]
		{
			PauseDay = true;
			VisitorManager->SetupNewVisitor(VisitorList[CurrentVisitorIndex]);
		},15,false);
	}
}
