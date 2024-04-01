// Fill out your copyright notice in the Description page of Project Settings.

#include "DetectorBuildTool.h"
#include "HopperInput.h"
#include "HopperOutput.h"
#include "PlayerControllerC.h"

// Sets default values
ADetectorBuildTool::ADetectorBuildTool()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetRelativeScale3D(FVector(0.1f));
    Mesh->SetVisibility(false, true);
    RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ADetectorBuildTool::BeginPlay()
{
    Super::BeginPlay();
    Mesh->OnComponentBeginOverlap.AddDynamic(this, &ADetectorBuildTool::BeginOverlap);
    Mesh->OnComponentEndOverlap.AddDynamic(this, &ADetectorBuildTool::EndOverlap);
    // bGenerateOverlapEventsDuringLevelStreaming = true;
}

// Called every frame
void ADetectorBuildTool::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADetectorBuildTool::BeginOverlap(UPrimitiveComponent *OverlapComponent, AActor *OtherActor,
                                      UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult &SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("begin: %s"), *OtherActor->GetName());
 
    this->PlayerController->Overlap = Cast<AMachine>(OtherActor);
}

void ADetectorBuildTool::EndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                    UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex)
{
    // UE_LOG(LogTemp, Warning, TEXT("End: %s"), *OtherActor->GetName());
  this->PlayerController->Overlap = nullptr;
}
