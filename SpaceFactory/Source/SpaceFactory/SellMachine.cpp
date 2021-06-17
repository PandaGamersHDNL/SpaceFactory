// Fill out your copyright notice in the Description page of Project Settings.


#include "SellMachine.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllerC.h"

ASellMachine::ASellMachine()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASellMachine::Tick(float DeltaTime)
{
    //cast<APlayerControllerC>(GetPlayerController(GetWorld(),))
    //get player controller (maybe give machine object owner objects -> player who spawned it for multiplayer)
    //add the price * amount to the players money
	Super::Tick(DeltaTime);
    //ItemToSell->Price;
    if(OwnerController && ItemToSell){

        OwnerController->Money += ItemToSell->Price * ItemToSell->Amount;
        ItemToSell->Destroy();
        ItemToSell = nullptr;
        //UE_LOG(LogTemp, Warning, TEXT("%s"),);
    }
    

}
