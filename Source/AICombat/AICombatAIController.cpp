// Fill out your copyright notice in the Description page of Project Settings.


#include "AICombatAIController.h"


#include "AICombatCharacter.h"
#include "BlackBoardKeys.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
AAICombatAIController::AAICombatAIController()
{
	SetupPerception();
}

void AAICombatAIController::SetupPerception()
{
	_sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (_sightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		_sightConfig->SightRadius = 5000.0f;
		_sightConfig->LoseSightRadius = _sightConfig->SightRadius + 250.0f;
		_sightConfig->PeripheralVisionAngleDegrees = 90.0f;
		_sightConfig->SetMaxAge(5.0f);
		_sightConfig->AutoSuccessRangeFromLastSeenLocation = 5000.0f;
		_sightConfig->DetectionByAffiliation.bDetectEnemies =
			_sightConfig->DetectionByAffiliation.bDetectFriendlies =
			_sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		// add sight configuration component to perception component
		GetPerceptionComponent()->SetDominantSense(*_sightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAICombatAIController::OnTargetPerceptionUpdated);
		GetPerceptionComponent()->ConfigureSense(*_sightConfig);
	}
}

void AAICombatAIController::OnTargetPerceptionUpdated(AActor* actor, FAIStimulus const stimulus)
{
	if (stimulus.Type.Name == "Default__AISense_Sight")
	{
		if (Cast<APawn>(actor) != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
		{
			OnTargetPercieved(actor, stimulus.WasSuccessfullySensed());
		}
	}
}

void AAICombatAIController::OnTargetPercieved(AActor* target, bool percieved)
{
	Blackboard->SetValueAsObject("TargetActor", percieved ? target : nullptr);

	if (percieved)
	{
		CurrentTargetActor = target;
		StartFight();
	}
	else
	{
		CurrentTargetActor = nullptr;
		EndFight();
	}
}

void AAICombatAIController::StartFight()
{
	auto* self = Cast<AAICombatCharacter>(GetPawn());

	self->SetOverlayState(EALSOverlayState::Rifle);
	self->SetRotationMode(EALSRotationMode::Aiming);
	SetFocus(CurrentTargetActor);
}

void AAICombatAIController::EndFight()
{
	auto* self = Cast<AAICombatCharacter>(GetPawn());

	self->SetOverlayState(EALSOverlayState::Default);
	self->SetRotationMode(EALSRotationMode::LookingDirection);
	ClearFocus(EAIFocusPriority::Gameplay);
}