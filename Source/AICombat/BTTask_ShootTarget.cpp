// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShootTarget.h"
#include <AIController.h>
#include "AICombatCharacter.h"
UBTTask_ShootTarget::UBTTask_ShootTarget()
{
}

EBTNodeResult::Type UBTTask_ShootTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* controller = Cast<AAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* character = Cast<AAICombatCharacter>(controller->GetPawn()))
		{
			character->Fire();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}