// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FightTargetService.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AttrubiteComponent.h"
#include "AICombatAIController.h"
#include "AICombatCharacter.h"
#include "AIController.h"

void UBTService_FightTargetService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                             float DeltaSeconds)
{
	if (auto* AIController = Cast<AAICombatAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* target = Cast<AAICombatCharacter>(AIController->GetCurrentTarget()))
		{
			if (UAttrubiteComponent::IsActorAlive(target))
			{
				LastKnownPosition = target->GetActorLocation();
				TargetWasAcquired = true;
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(HasValidTargetKey.SelectedKeyName, true);
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(HasValidTargetKey.SelectedKeyName, false);
				AIController->SetCurrentTarget(nullptr);
				AIController->EndFight();
				TargetWasAcquired = false;
				LastKnownPosition = AIController->GetPawn()->GetActorLocation();
			}

		}
		else if (TargetWasAcquired)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(HasValidTargetKey.SelectedKeyName, false);
			
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TargetLostKey.SelectedKeyName, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(LastKnownPositionKey.SelectedKeyName, LastKnownPosition);
			TargetWasAcquired = false;

		}
	}
}
