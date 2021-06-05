// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyMachine.h"
#include "Item.h"
#include "HopperOutput.h"

void ABuyMachine::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABuyMachine::SpawnItem, 1.0f, true, 0.0f);
	//GetWorldTimerManager().SetTimer<>
}

void ABuyMachine::SpawnItem()
{
	if (!OutputItem)
	{
		FActorSpawnParameters Params;
		OutputItem = GetWorld()->SpawnActor<AItem>(SpawnClass.Get(), FVector(GetActorLocation()), FRotator(GetActorRotation()), Params);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputItem->GetName())
	} 
}
