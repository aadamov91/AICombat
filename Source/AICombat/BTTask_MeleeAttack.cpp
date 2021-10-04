// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"


#include "AICombatCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto* pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (auto* character = Cast<AAICombatCharacter>(pawn))
	{
		//character->MeleeAtack();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
