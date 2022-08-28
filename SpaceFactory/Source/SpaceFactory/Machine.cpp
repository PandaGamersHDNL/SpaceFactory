// Fill out your copyright notice in the Description page of Project Settings.

#include "Machine.h"
#include "DetectorBuildTool.h"
#include "PlayerControllerC.h"

// Sets default values
AMachine::AMachine()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMachine::BeginPlay()
{
    Super::BeginPlay();
    // GetNetOwningPlayer()->GetPlayerController()
    OwnerController = GetWorld()->GetFirstPlayerController<APlayerControllerC>();
}

// Called every frame
void AMachine::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AMachine::BuildSelf(ADetectorBuildTool *BuildTool)
{
    UE_LOG(LogTemp, Warning, TEXT("BuildSelf"));
    return true;
}

