// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckHealth.h"
#include "AttrubiteComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		if (UAttrubiteComponent* AttribComp = Cast<UAttrubiteComponent>(Pawn->GetComponentByClass(UAttrubiteComponent::StaticClass())))
		{
			const bool lowHealth = AttribComp->GetHealth() / AttribComp->GetHealthMax() < HealthFraction;
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), lowHealth);
		}
	}
}