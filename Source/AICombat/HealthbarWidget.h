// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "HealthbarWidget.generated.h"

/**
 * 
 */
UCLASS()
class AICOMBAT_API UHealthbarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHPFraction(float HPFraction) const { if (HProgressBar) HProgressBar->SetPercent(HPFraction); }
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HProgressBar = nullptr;
	float CurrentHPFraction = 1.f;
};
