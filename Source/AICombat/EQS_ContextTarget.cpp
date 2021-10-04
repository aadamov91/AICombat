// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS_ContextTarget.h"


#include "AICombatAIController.h"
#include "AICombatCharacter.h"
#include "AI/ALSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"


void UEQS_ContextTarget::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);
	
	auto* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	ensure(QueryOwner);
	if (auto* AIController = Cast<AAICombatAIController>(QueryOwner->GetInstigatorController()))
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, AIController->GetCurrentTarget());
	}
}
