// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetPatrolPoint.generated.h"

/**
 * 
 */
UENUM()
enum class PatrolType
{
	Cycle = 0,
	BackAndForward
};

UCLASS()
class AICOMBAT_API UBTTask_GetPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector PatrolPointKey;

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowPrivateAccess = "true"))
	PatrolType PatrollingType = PatrolType::Cycle;
};
