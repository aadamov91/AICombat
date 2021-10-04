// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_OverrideAnimStance.h"
#include "AIController.h"
#include "Character/ALSBaseCharacter.h"

UBTTask_OverrideAnimStance::UBTTask_OverrideAnimStance()
{
	
}

EBTNodeResult::Type UBTTask_OverrideAnimStance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* character = Cast<AALSBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		character->SetOverlayState(OverlayState);
		character->SetRotationMode(RotationMode);
		character->SetStance(Stance);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}