// Fill out your copyright notice in the Description page of Project Settings.

		
#include "PlayerControllerC.h"

//APlayerControllerC::APlayerControllerC(){}

void APlayerControllerC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isInBuildMode && MachineBuilding)
	{
		UE_LOG(LogTemp, Warning, TEXT("test"));
	}
}



