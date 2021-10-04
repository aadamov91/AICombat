// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FightTargetService.generated.h"

/**
 * 
 */
UCLASS()
class AICOMBAT_API UBTService_FightTargetService : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector HasValidTargetKey;

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector TargetLostKey;
	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector LastKnownPositionKey;
	
	void ResetService();
	bool TargetWasAcquired = false;
	bool TargetLost = false;
	bool TargetDead = false;
	FVector LastKnownPosition {};
};
