// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToTarget.h"
#include <AIController.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto* target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());

	if (auto* actor = Cast<AActor>(target))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(OwnerComp.GetAIOwner(), actor->GetActorLocation());
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}