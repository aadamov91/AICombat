// Fill out your copyright notice in the Description page of Project Settings.


#include "AttrubiteComponent.h"

// Sets default values for this component's properties

UAttrubiteComponent::UAttrubiteComponent()
{
	HealthMax = 100;
	Health = HealthMax;

	SetIsReplicatedByDefault(true);
}


bool UAttrubiteComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}


bool UAttrubiteComponent::IsAlive() const
{
	return Health > 0.0f;
}


bool UAttrubiteComponent::IsFullHealth() const
{
	return Health == HealthMax;
}


float UAttrubiteComponent::GetHealth() const
{
	return Health;
}

float UAttrubiteComponent::GetHealthMax() const
{
	return HealthMax;
}


bool UAttrubiteComponent::ApplyHealthChange(AActor* InstigatorActor, float DeltaHP)
{
	if (!GetOwner()->CanBeDamaged() && DeltaHP < 0.0f)
	{
		return false;
	}

	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + DeltaHP, 0.0f, HealthMax);
	Health = NewHealth;
	float ActualDelta = NewHealth - OldHealth;

	if (ActualDelta != 0.0f)
	{
		OnHealthChanged.Broadcast(InstigatorActor, this, Health / HealthMax, DeltaHP);
	}

	return true;
}


UAttrubiteComponent* UAttrubiteComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UAttrubiteComponent>(FromActor->GetComponentByClass(UAttrubiteComponent::StaticClass()));
	}

	return nullptr;
}


bool UAttrubiteComponent::IsActorAlive(AActor* Actor)
{
	UAttrubiteComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

