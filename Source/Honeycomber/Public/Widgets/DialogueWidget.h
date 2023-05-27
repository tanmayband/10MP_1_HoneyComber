// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

class UCanvasPanel;
class UImage;
class UTextBlock;

UCLASS()
class HONEYCOMBER_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupDialogueWidget(FVector2D pivot);
	void UpdateDialogueLine(FString dialogueLine);
	void SetDialogueBGColour(FLinearColor newBGColour);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UCanvasPanel* Container;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UImage* DialogueBG;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* DialogueText;
};
