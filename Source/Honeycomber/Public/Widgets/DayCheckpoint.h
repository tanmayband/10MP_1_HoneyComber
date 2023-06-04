// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DayCheckpoint.generated.h"

class UImage;
class UTextBlock;
class UWidgetAnimation;

DECLARE_DELEGATE_OneParam(FDayAnimDoneSignature, bool isStartDay)

UCLASS()
class HONEYCOMBER_API UDayCheckpoint : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupCheckpoint(uint8 dayNum);
	void UpdateDayCount();
	void StartDayAnim();
	void EndDayAnim();
	void GameOverAnim();

	FDayAnimDoneSignature OnDayAnimDoneDelegate;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UImage* IrisBG;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* DayText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* MoneyText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* BeesText;
	UMaterialInstanceDynamic* BGMaterial;

	UPROPERTY(EditAnywhere, Interp)
		float CurrentBGRadius;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* DayIn;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* DayOut;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* GameOver;

	UFUNCTION(BlueprintCallable)
		void SetBGRadius(float newRadius);
	UFUNCTION(BlueprintCallable)
		void StartDayAnimDone();
	UFUNCTION(BlueprintCallable)
		void EndDayAnimDone();
};
