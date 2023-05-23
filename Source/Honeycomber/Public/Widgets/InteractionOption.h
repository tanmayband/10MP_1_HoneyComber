// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionOption.generated.h"

class UTextBlock;

UCLASS()
class HONEYCOMBER_API UInteractionOption : public UUserWidget
{
	GENERATED_BODY()

public:
	void PreConstruct(bool IsDesignTime);

	void SetupOption(FString option);
	void ToggleSelectOption(bool selected);

	void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UWidget* OptionBG;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* OptionName;
};
