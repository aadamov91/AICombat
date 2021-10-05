// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#include "PatrolPath.h"
#include "Character/ALSCharacter.h"
#include "GameFramework/Character.h"
#include "AICombatCharacter.generated.h"

class UHealthbarWidget;
class UWidgetComponent;
class UAttrubiteComponent;

UCLASS(config=Game)
class AAICombatCharacter : public AALSCharacter
{
	GENERATED_BODY()
public:
	AAICombatCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttrubiteComponent* AttributeComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABulletProjectile> ProjectileClass;

	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UAttrubiteComponent* OwningComp, float NewHPFraction, float Delta);
	
	UFUNCTION()
	void Fire();
	
	APatrolPath* GetPatrolPath() const { return PatrolPath; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	APatrolPath* PatrolPath;
	
	UWidgetComponent* Widgets;

};

