// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerC.h"

#include "BuilderPawn.h"
#include "BuyMachine.h"
#include "Components/ArrowComponent.h"
#include "DetectorBuildTool.h"
#include "HopperInput.h"
#include "HopperOutput.h"
#include "PneumaticTube.h"

void APlayerControllerC::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("BuildMode", IE_Pressed, this, &APlayerControllerC::BuildModeActivate);
    // move to builder pawn maybe
    InputComponent->BindAction("BuildMachine", IE_Pressed, this, &APlayerControllerC::BuildMachine);
    InputComponent->BindAxis("RotateMachine", this, &APlayerControllerC::RotateMachine);
}

void APlayerControllerC::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = GetPawn();
    FActorSpawnParameters Params;
    Params.Name = TEXT("Builder");

    if (BuildingBp)
    {
        // SetControlRotation(FRotator(0.0f));
        BuilderPawn = GetWorld()->SpawnActor<ABuilderPawn>(BuildingBp.Get(), FVector(0.0f, 0.0f, BuilderHeight),
                                                           FRotator(BuilderAngle, 0.0f, 0.0f), Params);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("please select a class to spawn for the builder pawn"));
    }
}

void APlayerControllerC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    float MouseX, MouseY;
    FVector Dir, Pos;
    GetMousePosition(MouseX, MouseY);
    if (isInBuildMode && DeprojectScreenPositionToWorld(MouseX, MouseY, Pos, Dir))
    {

        FVector BuildVector = (Pos + (((BuildHeight - Pos.Z) / Dir.Z) * Dir));
        if (DetectorBT)
        {
            DetectorBT->SetActorLocation(BuildVector, false);
        }
        if (MachineBuilding)
        {
            auto PneumaticTube = Cast<APneumaticTube>(MachineBuilding);
            if (PneumaticTube)
            {
                MoveSplinePoint(PneumaticTube, BuildVector);
                return;
            }

            MachineBuilding->SetActorLocation(BuildVector, false);
        }
        // UE_LOG(LogTemp, Warning, TEXT("%i"), SplinePoint);
    }
}

void APlayerControllerC::BuildModeActivate()
{
    if (BuilderPawn)
    {
        isInBuildMode = !isInBuildMode;
        if (isInBuildMode)
        {
            Possess(BuilderPawn);
            SetShowMouseCursor(true);
            FActorSpawnParameters Params;
            Params.Name = TEXT("DetectorBuilderTool");
            if (!DetectorBT)
            {
                DetectorBT = GetWorld()->SpawnActor<ADetectorBuildTool>(
                    DetectorBTBP.Get(), FVector(0.0f, 0.0f, BuilderHeight), FRotator(BuilderAngle, 0.0f, 0.0f), Params);
                DetectorBT->PlayerController = this;
                // DetectorBT->SetHidden(true);
            }
        }
        else
        {
            Possess(PlayerPawn);
            SetShowMouseCursor(false);
        }
        BuildingMenu(isInBuildMode);
    }
}

void APlayerControllerC::BuildMachine()
{
    // TODO handle
    if (!MachineBuilding)
        return;
    if (MachineBuilding->BuildSelf(DetectorBT))
    {
        MachineBuilding = nullptr;
    }
}

void APlayerControllerC::RotateMachine(float Scale)
{
    if (MachineBuilding)
    {
        MachineBuilding->SetActorRotation(
            FRotator(0.0f, MachineBuilding->GetActorRotation().Yaw + (MachineRotationSpeed * Scale), 0.0f));
    }
}

void APlayerControllerC::CreateMachine(TSubclassOf<AMachine> MachineClass)
{
    if (!MachineBuilding)
    {
        FActorSpawnParameters Params;
        MachineBuilding = GetWorld()->SpawnActor<AMachine>(MachineClass.Get(), FVector(0.0f, 0.0f, BuilderHeight),
                                                           FRotator(0, 0.0f, 0.0f), Params);
    }
}

// move to Pneumatic tube?
void APlayerControllerC::MoveSplinePoint(APneumaticTube *PneumaticTube, FVector BuildVector)
{
    if (SplinePoint == 0)
    {
        if (HopperOutput)
        {
            PneumaticTube->SetActorLocation(HopperOutput->GetActorLocation());
            /*+ HopperOutput->GetActorForwardVector() * SecondSplinePointDistance*/
            PneumaticTube->Spline->SetLocationAtSplinePoint(1, FVector(100, 0, 0), ESplineCoordinateSpace::Local);
            // PneumaticTube->Spline->SetTangentAtSplinePoint(SplinePoint, HopperOutput->GetActorForwardVector() *
            // TangentSize, ESplineCoordinateSpace::World, true);
        }
        else if (HopperInput)
        {
            PneumaticTube->SetActorLocation(HopperInput->GetActorLocation()
                                            /*+ HopperInput->GetActorForwardVector() * SecondSplinePointDistance*/);
            // PneumaticTube->Spline->SetTangentAtSplinePoint(SplinePoint, HopperInput->GetActorForwardVector() *
            // TangentSize, ESplineCoordinateSpace::World, true);
        }
        else
        {
            PneumaticTube->SetActorLocation(BuildVector, false, nullptr, ETeleportType::TeleportPhysics);
            PneumaticTube->Spline->SetLocationAtSplinePoint(1, FVector(100, 0, 0), ESplineCoordinateSpace::Local);
        }
    }
    else
    {
        // TODO Check if the output hopper for example is already set so we don't snap to the other output actors
        if (HopperOutput && bHopperOutput == false)
        {
            PneumaticTube->Spline->SetLocationAtSplinePoint(SplinePoint, HopperOutput->GetActorLocation(),
                                                            ESplineCoordinateSpace::World, true);
        }
        else if (HopperInput && bHopperInput == false)
        {
            PneumaticTube->Spline->SetLocationAtSplinePoint(SplinePoint, HopperInput->GetActorLocation(),
                                                            ESplineCoordinateSpace::World, true);
        }
        else
        {
            PneumaticTube->Spline->SetLocationAtSplinePoint(SplinePoint, BuildVector, ESplineCoordinateSpace::World,
                                                            true);
        }
    }
}
