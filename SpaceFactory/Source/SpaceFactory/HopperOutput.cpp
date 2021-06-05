// Fill out your copyright notice in the Description page of Project Settings.


#include "HopperOutput.h"
#include "PneumaticTube.h"
#include "Machine.h"

// Sets default values
AHopperOutput::AHopperOutput()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHopperOutput::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHopperOutput::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OutputItem();
}

void AHopperOutput::OutputItem()
{
	if (!PneumaticTube || !Machine)
		return; //null ptr prot

	if (PneumaticTube->TransportingItem)
		return; //tube busy
	if (!Machine->OutputItem)
		return; //no item
	PneumaticTube->TransportingItem = Machine->OutputItem;
	Machine->OutputItem = nullptr;
	
}

