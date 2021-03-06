// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(FRotator(0.0f, openAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.0f, 0.f, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	float actualTime = GetWorld()->GetTimeSeconds();
	if (GetTotalMassofActorsOnPlate() > 50.0f)
	{
		OpenDoor();
		lastDoorOpenTime = actualTime;
	}
	else
	{
		if (actualTime > lastDoorOpenTime + doorCloseDelay)
			CloseDoor();
	}
}

float UOpenDoor::GetTotalMassofActorsOnPlate()
{
	float totalMass = 0.f;
	TArray<AActor*> overlappingActors;

	pressurePlate->GetOverlappingActors(OUT overlappingActors);

	for (const AActor* actor : overlappingActors)
	{
		UPrimitiveComponent* primitiveActor = actor->FindComponentByClass<UPrimitiveComponent>();
		if(primitiveActor->IsSimulatingPhysics())
			totalMass += primitiveActor->GetMass();
	}

	return totalMass;
}