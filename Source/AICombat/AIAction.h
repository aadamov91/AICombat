// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIAction.generated.h"

/**
 * 
 */
UCLASS()
class AICOMBAT_API UAIAction : public UObject
{
public:
	GENERATED_BODY()
	UAIAction();
	~UAIAction();
	void ExecuteAction() {}
};
