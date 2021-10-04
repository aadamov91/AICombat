// Copyright Epic Games, Inc. All Rights Reserved.

#include "AICombatCharacter.h"

#include "AICombatAIController.h"
#include "BulletProjectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AttrubiteComponent.h"
#include <Components/WidgetComponent.h>

#include "HealthbarWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
//////////////////////////////////////////////////////////////////////////
// AAICombatCharacter

AAICombatCharacter::AAICombatCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttributeComp = CreateDefaultSubobject<UAttrubiteComponent>("AttributeComp");
	Widgets = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health"));
	Widgets->SetupAttachment(RootComponent);
	Widgets->SetWidgetSpace(EWidgetSpace::Screen);
	Widgets->SetRelativeLocation({ 0.f, 0.f, 85.f });
	static ConstructorHelpers::FClassFinder<UUserWidget> widgetClass(TEXT("/Game/UI/HPBarWidget_BP"));
	if (widgetClass.Succeeded())
	{
		Widgets->SetWidgetClass(widgetClass.Class);
	}
}

void AAICombatCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AAICombatCharacter::OnHealthChanged);

	if (auto* HPWidget = Cast<UHealthbarWidget>(Widgets->GetUserWidgetObject()))
	{
		HPWidget->SetHPFraction(1.f);
	}
}

void AAICombatCharacter::Fire()
{
	if (ProjectileClass)
	{
		auto obj = HeldObjectRoot;
		
		FVector Location = obj->GetComponentLocation(); // todo spawn from heldObject
		FRotator Rotation = GetAimingRotation();

		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		FVector MuzzleLocation = Location + FTransform(Rotation).TransformVector(MuzzleOffset);

		FRotator MuzzleRotation = Rotation;
		auto spread = AttributeComp->GetBulletSpread();
		MuzzleRotation.Pitch += FMath::RandRange(0.0f, spread);
		MuzzleRotation.Yaw += FMath::RandRange(-spread, spread);
		if (UWorld* World = GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			
			if (ABulletProjectile* Projectile = World->SpawnActor<ABulletProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams))
			{
				Projectile->FireInDirection(MuzzleRotation.Vector());
			}
		}
	}
}

void AAICombatCharacter::OnHealthChanged(AActor* InstigatorActor, UAttrubiteComponent* OwningComp, float NewHPFraction,
	float Delta)
{
	if (InstigatorActor != this)
	{
		if (auto* AIController = Cast<AAICombatAIController>(GetController()))
		{
			AIController->SetCurrentTarget(InstigatorActor);
		}

		if (auto* HPWidget = Cast<UHealthbarWidget>(Widgets->GetUserWidgetObject()))
		{
			HPWidget->SetHPFraction(NewHPFraction);
		}
	}
	if (FMath::IsNearlyZero(NewHPFraction))
	{
		if (auto* AIController = Cast<AAICombatAIController>(GetController()))
		{
			AIController->GetBrainComponent()->StopLogic("Killed");
		}

		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName("Ragdoll");

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCharacterMovement()->DisableMovement();

		SetLifeSpan(100.0f);
	}
}
