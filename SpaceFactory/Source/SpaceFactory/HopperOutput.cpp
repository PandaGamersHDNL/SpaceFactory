// Fill out your copyright notice in the Description page of Project Settings.


#include "HopperOutput.h"
#include "PneumaticTube.h"
#include "ProcessMachine.h"
#include "DetectorBuildTool.h"
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

bool AHopperOutput::BuildSelf(ADetectorBuildTool *BuildTool)
{
  FHitResult Hit;
  FVector Start = GetActorLocation();
  FRotator Rot = GetActorRotation();
  auto Params = FCollisionQueryParams();
  Params.AddIgnoredActor(this);
  Params.AddIgnoredActor(BuildTool);
  for (int i = 0; i < 4; i++)
  {
    UE_LOG(LogTemp, Warning, TEXT("end vector is %s for HopperOutput"), *(Start + (Rot.Vector() * DetectDistance)).ToString());
    GetWorld()->LineTraceSingleByChannel(Hit, Start, Start + (Rot.Vector() * DetectDistance), ECollisionChannel::ECC_Visibility, Params);
    if (Hit.GetActor())
      UE_LOG(LogTemp, Warning, TEXT("hit actor: %s for HopperOutput:"), *Hit.GetActor()->GetName());
    Rot.Yaw += 90;
    auto HitMachine = Cast<AProcessMachine>(Hit.GetActor());
    if (HitMachine && !HitMachine->HopperOutput)
    {
      UE_LOG(LogTemp, Warning, TEXT("assigned machine as: %s for HopperOutput: %s"), *HitMachine->GetName(), *GetName());
      Machine = HitMachine;
      HitMachine->HopperOutput = this;
      return true;
    }
  }
  UE_LOG(LogTemp, Warning, TEXT("Failed assigning a machine"));
  return false;
}

