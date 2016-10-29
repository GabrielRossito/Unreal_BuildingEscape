// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PosistionReporter.h"


// Sets default values for this component's properties
UPosistionReporter::UPosistionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPosistionReporter::BeginPlay()
{
	Super::BeginPlay();

	FString objName = GetOwner()->GetName();
	FString objPos = GetOwner()->GetActorTransform().GetLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *objName, *objPos);
}


// Called every frame
void UPosistionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

