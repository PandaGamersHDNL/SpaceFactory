// Fill out your copyright notice in the Description page of Project Settings.

#include "HopperInput.h"
#include "PneumaticTube.h"
#include "ProcessMachine.h"
#include "SellMachine.h"

void AHopperInput::InputItem()
{
  if (!PneumaticTube || !Machine)
    return; //null ptr prot
  ASellMachine *SellMachine = Cast<ASellMachine>(Machine);
  //check other first it is more likely

  if (SellMachine && !SellMachine->ItemToSell)
  {
    SellMachine->ItemToSell = PneumaticTube->TransportingItem;
    PneumaticTube->TransportingItem = nullptr;
    PneumaticTube->ItemDistance = 0;
    return;
  }
  /*if (!PneumaticTube->TransportingItem)
		return; //tube not busy, already checked before func call*/
  /*if (!)
		return false; //no item*/
}