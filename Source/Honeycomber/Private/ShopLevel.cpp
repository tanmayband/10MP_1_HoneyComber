// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopLevel.h"
#include "Actors/VisitorManager.h"
#include "Engine/DirectionalLight.h"
#include "Widgets/DayCheckpoint.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/BeehiveManagerSubsystem.h"

AShopLevel::AShopLevel()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShopLevel::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->SetIgnoreMoveInput(true);

	Daylight->SetActorRotation(FRotator(90, 0, 0));

	VisitorManager->SetupVisitorManager();
	VisitorManager->OnVisitorDoneDelegate.BindUObject(this, &AShopLevel::NextVisitor);

	DayCheckpointWidget = CreateWidget<UDayCheckpoint>(UGameplayStatics::GetPlayerController(GetWorld(), 0), DayCheckpointWidgetClass);
	//DayCheckpointWidget->AddToViewport();
	DayCheckpointWidget->OnDayAnimDoneDelegate.BindLambda([&](bool isStartDay)
	{
		if (isStartDay)
		{
			PauseDay = false;
			GetWorld()->GetFirstPlayerController()->SetIgnoreMoveInput(false);
		}
		else
		{
			UBeehiveManagerSubsystem* beehiveSubsystem = GetGameInstance()->GetSubsystem<UBeehiveManagerSubsystem>();
			uint8 beesLeft = beehiveSubsystem->UpdateAllBees();
			if (beesLeft > 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Day end"));
				DayNum += 1;
				ResetDay();
			}
			else
			{
				DayCheckpointWidget->GameOverAnim();
			}
		}
	});

	ResetDay();
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
			GetWorld()->GetFirstPlayerController()->SetIgnoreMoveInput(true);
			DayCheckpointWidget->EndDayAnim();
		}
		else if (!VisitorsStarted && DayProgress >= 0.2)
		{
			VisitorsStarted = true;
			NextVisitor();
		}
	}
}

void AShopLevel::ResetDay()
{
	DayProgress = 0;
	CurrentVisitorIndex = -1;
	VisitorsStarted = false;
	DayCheckpointWidget->SetupCheckpoint(DayNum);
	SetupTodaysVisitors();
	
	/*FTimerHandle nextDayHandle;
	GetWorldTimerManager().SetTimer(nextDayHandle, [&]
	{
		DayCheckpointWidget->StartDayAnim();
	}, 3, false);*/
	PauseDay = false;
	GetWorld()->GetFirstPlayerController()->SetIgnoreMoveInput(false);
}

void AShopLevel::SetupTodaysVisitors()
{
	TodayVisitorList.Empty();
	UDataTable* TodaysVisitorTable = DaysVisitorTables[DayNum - 1];
	TodaysVisitorTable->GetAllRows("Converting visitors table to array", TodayVisitorList);
}

void AShopLevel::NextVisitor()
{
	PauseDay = false;
	if (++CurrentVisitorIndex < TodayVisitorList.Num())
	{
		// go to next visitor after a delay
		FTimerHandle visitorHandle;
		GetWorldTimerManager().SetTimer(visitorHandle, [&]
		{
			PauseDay = true;
			VisitorManager->SetupNewVisitor(*TodayVisitorList[CurrentVisitorIndex]);
		},15,false);
	}
}
