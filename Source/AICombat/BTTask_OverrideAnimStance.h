// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Library/ALSCharacterEnumLibrary.h"
#include "BTTask_OverrideAnimStance.generated.h"

/**
 * 
 */
UCLASS(Category = COMBAT, meta = (DisplayName = "OverrideAnimStance"))
class AICOMBAT_API UBTTask_OverrideAnimStance : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_OverrideAnimStance();
	UPROPERTY(BlueprintReadWrite, Category = AI, EditAnywhere)
	EALSOverlayState OverlayState = EALSOverlayState::Default;

	UPROPERTY(BlueprintReadWrite, Category = AI, EditAnywhere)
	EALSRotationMode RotationMode = EALSRotationMode::VelocityDirection;

	UPROPERTY(BlueprintReadWrite, Category = AI, EditAnywhere)
	EALSStance Stance = EALSStance::Standing;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
