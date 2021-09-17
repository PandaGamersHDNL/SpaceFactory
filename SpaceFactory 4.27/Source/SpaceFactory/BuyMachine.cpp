// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyMachine.h"
#include "Item.h"
#include "HopperOutput.h"

void ABuyMachine::BeginPlay()
{
	Super::BeginPlay();
	//TODO move on load
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABuyMachine::SpawnItem, 1.0f, true, 0.0f);
	//GetWorldTimerManager().SetTimer<>
}

void ABuyMachine::SpawnItem()
{
	if (SpawnClass && !OutputItem)
	{
		FActorSpawnParameters Params;
		OutputItem = GetWorld()->SpawnActor<AItem>(SpawnClass.Get(), FVector(GetActorLocation()), FRotator(GetActorRotation()), Params);
	} 
}

void ABuyMachine::StartTimer() {
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABuyMachine::SpawnItem, 1.0f, true, 0.0f);
}