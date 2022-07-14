// Fill out your copyright notice in the Description page of Project Settings.

#include "PneumaticTube.h"
#include "Components/SplineMeshComponent.h"
#include "DetectorBuildTool.h"
#include "HopperInput.h"
#include "HopperOutput.h"
#include "Item.h"
#include "PlayerControllerC.h"

// Sets default values
APneumaticTube::APneumaticTube()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    /*SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SceneComponent->SetMobility(EComponentMobility::Static);*/

    Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    Spline->SetMobility(EComponentMobility::Movable);
    Spline->SetLocationAtSplinePoint(0, FVector(0.0f), ESplineCoordinateSpace::Local, true);
    // Spline->AddSplinePoint(FVector(110.0f, 0.0f, 0.0f),                         ESplineCoordinateSpace::Local, true);
    Spline->SetLocationAtSplinePoint(1, FVector(110.0f, 0.0f, 0.0f), ESplineCoordinateSpace::Local, true);
    UE_LOG(LogTemp, Warning, TEXT("%i"), Spline->GetNumberOfSplinePoints());
    RootComponent = Spline;
    Spline->bDrawDebug = true;
    Spline->SetVisibility(true);
    bGenerateOverlapEventsDuringLevelStreaming = true;
    UE_LOG(LogTemp, Error, TEXT("%s %d there were spline %d points"), __FILEW__, __LINE__,
           Spline->GetNumberOfSplinePoints());
}

// Called when the game starts or when spawned
void APneumaticTube::BeginPlay()
{
    Super::BeginPlay();
    Spline->OnComponentBeginOverlap.AddDynamic(this, &APneumaticTube::OnBeginOverlap);
}

// Called every frame
void APneumaticTube::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MoveItem(DeltaTime);
}

void APneumaticTube::OnBeginOverlap(UPrimitiveComponent *OverlapComponent, AActor *OtherActor,
                                    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult &SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("begin overlap"));
}

void APneumaticTube::MoveItem(float DeltaTime)
{
    if (!TransportingItem)
    {
        return;
    }
    ItemDistance += (DeltaTime * TransportSpeed);
    TransportingItem->SetActorLocation(
        Spline->GetLocationAtDistanceAlongSpline(ItemDistance, ESplineCoordinateSpace::World), false);
    FRotator rotation = Spline->GetRotationAtDistanceAlongSpline(ItemDistance, ESplineCoordinateSpace::Local);
    // UE_LOG(LogTemp, Warning, TEXT("rotation at item distance %s"), *rotation.ToString());
    TransportingItem->SetActorRotation(rotation + this->GetActorRotation());

    if (Spline->GetSplineLength() - 10.0f < ItemDistance) // TODO make 10.0f var for editor
    {
        // put in input hopper?
        TransportingItem->SetActorLocation(
            Spline->GetLocationAtDistanceAlongSpline(Spline->GetSplineLength(), ESplineCoordinateSpace::World), false);
        if (HopperInput)
        {
            HopperInput->InputItem();
        }
        // call the inputhopper to add to input
    }
}

bool APneumaticTube::BuildSelf(ADetectorBuildTool *BuildTool)
{
    //  3, on click with input hopper end build cycle
    // step 1 set output hopper (input of tube)
    if (!this->HopperOutput && this->OwnerController->Overlap)
    {
        auto outputH = Cast<AHopperOutput>(this->OwnerController->Overlap);
        if (outputH)
        {
            this->HopperOutput = outputH;
            this->OwnerController->SplinePoint += 2;

            this->Spline->SetLocationAtSplinePoint(
                1, this->GetActorLocation() + (this->GetActorRotation().Vector() * 100.0f),
                ESplineCoordinateSpace::World, true);
            this->Spline->AddSplinePoint(BuildTool->GetActorLocation(),
                                         ESplineCoordinateSpace::World, true);

            UE_LOG(LogTemp, Warning, TEXT("there is hopper output"));
        }
        return false;
    }
    UE_LOG(LogTemp, Warning, TEXT("hopper output set"));

    // step 2 add spline points
    if (!this->OwnerController->Overlap)
    {
        UE_LOG(LogTemp, Error, TEXT("%s %d there were spline %d points"), __FILEW__, __LINE__,
               Spline->GetNumberOfSplinePoints());
        this->OwnerController->SplinePoint++;
        this->Spline->AddSplinePoint(BuildTool->GetActorLocation(), ESplineCoordinateSpace::World, true);
    }
    else
    {
        // step 3 set input hopper
        auto hopperI = Cast<AHopperInput>(this->OwnerController->Overlap);
        if (hopperI)
        {
            this->HopperInput = hopperI;
            // UE_LOG(LogTemp, Error, TEXT("%s %d there were spline %d points FINISHED BUILDING"),__FILEW__, __LINE__,
            // Spline->GetNumberOfSplinePoints());
            this->HopperInput->PneumaticTube = this;
            this->HopperOutput->PneumaticTube = this;
            return true;
        }
    }
    return false;
}
