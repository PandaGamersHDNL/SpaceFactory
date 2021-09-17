// Fill out your copyright notice in the Description page of Project Settings.

#include "HopperInput.h"
#include "PneumaticTube.h"
#include "ProcessMachine.h"
#include "SellMachine.h"
#include "DetectorBuildTool.h"

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

bool AHopperInput::BuildSelf(ADetectorBuildTool *BuildTool)
{
  FHitResult Hit;
  FVector Start = GetActorLocation();
  FRotator Rot = GetActorRotation();
  auto Params = FCollisionQueryParams();
  Params.AddIgnoredActor(this);
  Params.AddIgnoredActor(BuildTool);
  for (int i = 0; i < 4; i++)
  {
    UE_LOG(LogTemp, Warning, TEXT("end vector is %s for HopperInput"), *(Start + (Rot.Vector() * DetectDistance)).ToString());
    GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + (Rot.Vector() * DetectDistance), ECollisionChannel::ECC_Visibility, Params);
    if (Hit.GetActor())
      UE_LOG(LogTemp, Warning, TEXT("hit actor: %s for HopperInput:"), *Hit.GetActor()->GetName());
    Rot.Yaw += 90;
    auto HitMachine = Cast<AProcessMachine>(Hit.GetActor());
    if (HitMachine && !HitMachine->HopperInput)
    {
      UE_LOG(LogTemp, Warning, TEXT("assigned machine as: %s for HopperInput: %s"), *HitMachine->GetName(), *GetName());
      Machine = HitMachine;
      HitMachine->HopperInput = this;
      return true;
    }
  }
  UE_LOG(LogTemp, Warning, TEXT("Failed assigning a machine"));
  return false;
}
