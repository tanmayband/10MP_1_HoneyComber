// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopLevel.h"
#include "Actors/VisitorManager.h"

void AShopLevel::BeginPlay()
{
	Super::BeginPlay();
	VisitorManager->SetupVisitorManager();
	VisitorManager->OnVisitorDoneDelegate.BindUObject(this, &AShopLevel::NextVisitor);
	NextVisitor();
}

void AShopLevel::NextVisitor()
{
	if (++CurrentVisitorIndex < VisitorList.Num())
		VisitorManager->SetupNewVisitor(VisitorList[CurrentVisitorIndex]);
	else
		UE_LOG(LogTemp, Warning, TEXT("End of day."));
}
