// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/ALSAIController.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

#include "AICombatAIController.generated.h"

UCLASS()
class AICOMBAT_API AAICombatAIController : public AALSAIController
{
	GENERATED_BODY()
public:
	AAICombatAIController();
	
	AActor* GetCurrentTarget() const { return CurrentTargetActor; }
	void SetCurrentTarget(AActor* target) { CurrentTargetActor = target; }
	
protected:
	UAISenseConfig_Sight* _sightConfig;

	AActor* CurrentTargetActor;
	
	void SetupPerception();

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* actor, FAIStimulus const stimulus);

	UFUNCTION()
	void OnTargetPercieved(AActor* target, bool percieved);
public:	
	void StartFight();
	void EndFight();

};
