// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AIAction.h"

#include "AIAction.h"

EBTNodeResult::Type UBTTask_AIAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIAction->ExecuteAction();
	return EBTNodeResult::Succeeded;
}
