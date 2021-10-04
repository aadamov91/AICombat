// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent())
	{
		AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* Controller = OwnerComp.GetAIOwner();

			if (APawn* AIPawn = Controller->GetPawn())
			{
				const float Distance = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
				const bool InRange = Distance < MaxAttackRange;

				BBComp->SetValueAsBool(GetSelectedBlackboardKey(), InRange && Controller->LineOfSightTo(TargetActor));
			}
		}
	}
}