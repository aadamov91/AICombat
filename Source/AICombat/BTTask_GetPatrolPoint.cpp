// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AICombatAIController.h"
#include "AICombatCharacter.h"

EBTNodeResult::Type UBTTask_GetPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto* npc = Cast<AAICombatCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (const auto* patrolPath = npc->GetPatrolPath())
	{
		size_t index = OwnerComp.GetBlackboardComponent()->GetValueAsInt(GetSelectedBlackboardKey());
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolPointKey.SelectedKeyName, patrolPath->GetPatrolPointInWorld(index));
		//if (index == patrolPath->GetPatrolPoints().Num() - 1)
		//{
		//	switch (PatrollingType)
		//	{
		//	case PatrolType::BackAndForward:
		//		{
		//		OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), --index);
		//		break;
		//		}
		//	}
		//}
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), index == patrolPath->GetPatrolPoints().Num() - 1 ? 0 : ++index);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;

}
