// Fill out your copyright notice in the Description page of Project Settings.


#include "SellMachine.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "itemInfo.h"
#include "PlayerControllerC.h"

ASellMachine::ASellMachine()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASellMachine::Tick(float DeltaTime)
{
    //cast<APlayerControllerC>(GetPlayerController(GetWorld(),))
    //get player controller (maybe give machine object owner objects -> player who spawned it for multiplayer)
    
	Super::Tick(DeltaTime);
    SellItem();
}

void ASellMachine::SellItem(){
    if(OwnerController && ItemTable && ItemToSell){
        FItemInfo* ItemData = ItemTable->FindRow<FItemInfo>(ItemToSell->ItemKey,"ItemDataSellMachine" , true);
        if(!ItemData)  { return;
            UE_LOG(LogTemp, Warning, TEXT("No ItemData"));
        }
        //UE_LOG(LogTemp, Warning, TEXT("%d"), ItemData->PriceSell)
        OwnerController->Money +=  ItemData->PriceSell * ItemToSell->Amount; //make protected and use function?  
        if(ItemToSell->Destroy())
        {
            //OwnerController->Money += ItemToSell->Price * ItemToSell->Amount; //do here so we can change vars only if it is marked for destruction? TEST if works
            ItemToSell = nullptr;
        }
        //UE_LOG(LogTemp, Warning, TEXT("%s"),);
    }
}