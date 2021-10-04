// Fill out your copyright notice in the Description page of Project Settings.

#include "BuyMachine.h"
#include "Item.h"
#include "itemInfo.h"
#include "PlayerControllerC.h"
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
	if (SpawnClass && OwnerController && ItemTable && !OutputItem)
	{
		if (!SpawnedItem)
		{
			FActorSpawnParameters Params;
			SpawnedItem = GetWorld()->SpawnActor<AItem>(SpawnClass.Get(), FVector(GetActorLocation()), FRotator(GetActorRotation()), Params);
			UE_LOG(LogTemp, Warning, TEXT("Spawned"));
		}
		FItemInfo *ItemData = ItemTable->FindRow<FItemInfo>(SpawnedItem->ItemKey, "BuyMachineItemInfoTable", true);
		if (SpawnedItem && ItemData && OwnerController->Money >= ItemData->PriceBuy)
		{
			OwnerController->Money -= ItemData->PriceBuy;
			OutputItem = SpawnedItem;
			SpawnedItem = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Exported, payed: %d"), ItemData->PriceBuy);
		}
	}
}

void ABuyMachine::StartTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABuyMachine::SpawnItem, 1.0f, true, 0.0f);
}