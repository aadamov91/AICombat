// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetPosition.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Pawn->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}