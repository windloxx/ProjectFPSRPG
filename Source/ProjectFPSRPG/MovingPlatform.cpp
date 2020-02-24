// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);

}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GloablStartLoacation = GetActorLocation();
	GloablTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		float JourneyLength = (GloablTargetLocation - GloablStartLoacation).Size();
		float JourneyTravelled = (Location - GloablStartLoacation).Size();

		if (JourneyTravelled > JourneyLength)
		{
			FVector Swap = GloablStartLoacation;
			GloablStartLoacation = GloablTargetLocation;
			GloablTargetLocation = Swap;
		}

		FVector Direction = (GloablTargetLocation - GloablStartLoacation).GetSafeNormal();
		Location += Speed * DeltaTime * Direction;
		SetActorLocation(Location);

	}
	
}

