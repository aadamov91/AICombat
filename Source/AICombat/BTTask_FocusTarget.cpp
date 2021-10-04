// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FocusTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <AIController.h>

EBTNodeResult::Type UBTTask_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto* target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	if (auto* actor = Cast<AActor>(target))
	{
		OwnerComp.GetAIOwner()->SetFocus(actor);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}