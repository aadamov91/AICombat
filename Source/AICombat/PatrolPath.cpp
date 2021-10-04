// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPath.h"

// Sets default values
APatrolPath::APatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FVector APatrolPath::GetPatrolPointInWorld(size_t index) const
{
	ensure(PatrolPoints.IsValidIndex(index));
	return GetActorTransform().TransformPosition(PatrolPoints[index]);
}

