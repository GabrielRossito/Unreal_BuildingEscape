// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	UOpenDoor();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor();
	void CloseDoor();

private:
	UPROPERTY(EditAnywhere)
		float openAngle = -60.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* pressurePlate;


	UPROPERTY(EditAnywhere)
		float doorCloseDelay = 1.f;

	AActor* owner;
	float lastDoorOpenTime;
	float GetTotalMassofActorsOnPlate();
};
