// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class AICOMBAT_API UBTService_CheckAttackRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "10000.0"))
	float MaxAttackRange = 2000.f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
