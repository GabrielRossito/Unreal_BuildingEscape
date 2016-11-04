// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber ready!"));

	_physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	_inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (_inputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("OK !"));

		_inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		_inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::DesGrab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing _inputComponet!"));
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbing!"));
}

void UGrabber::DesGrab()
{
	UE_LOG(LogTemp, Warning, TEXT("DesGrabbing!"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	/*UE_LOG(LogTemp, Warning, TEXT("L:%s && P:%s"),
		*playerViewPointLocation.ToString(),
		*playerViewPointRotation.ToString()
	);*/
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * _reach;

	DrawDebugLine(
		GetWorld(),
		playerViewPointLocation,
		lineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	/// Setup query parameters
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

	/// Make raycast/line-trace
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		playerViewPointLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParameters
	);

	AActor* actorHit = hit.GetActor();
	//if (actorHit)
	//	UE_LOG(LogTemp, Warning, TEXT("Hit:%s"), *(actorHit->GetName()));
}

