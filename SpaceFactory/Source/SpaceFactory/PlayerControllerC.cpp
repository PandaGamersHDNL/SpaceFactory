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

UUserWidget *ui = nullptr;
void APlayerControllerC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    float MouseX, MouseY;
    FVector Dir, Pos;
    GetMousePosition(MouseX, MouseY);
    if (isInBuildMode && DeprojectScreenPositionToWorld(MouseX, MouseY, Pos, Dir))
    {
      /* UE_LOG(LogTemp, Warning, TEXT("overlap: %s, ui: %s"),
             Overlap ? TEXT("yes") : TEXT("no"),
             ui ? TEXT("yes") : TEXT("no"))*/
      if (Overlap) {
        /* UE_LOG(LogTemp, Warning, TEXT("overlap ui: %s"),
               Overlap->ui ? TEXT("yes") : TEXT("no"))*/
      if (Overlap->ui && !ui) {
        UE_LOG(LogTemp, Warning, TEXT("ui has been added to the view port"));
        
        ui = CreateWidget(this, Overlap->ui, FName("machine UI"));
        ui->AddToPlayerScreen();

      }
      }
        //TODO remove detector use raycast at build height (raycast vs collisions?)
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

// TODO move to Pneumatic tube
// TODO cast overlap to input/output
void APlayerControllerC::MoveSplinePoint(APneumaticTube *PneumaticTube, FVector BuildVector)
{
    if (SplinePoint == 0)
    {
        auto hopperO = Cast<AHopperOutput>(this->Overlap);
        if (hopperO)
        {
            UE_LOG(LogTemp, Warning, TEXT("move spline %s"), *hopperO->GetName());
            PneumaticTube->SetActorLocation(hopperO->GetActorLocation());
            PneumaticTube->Spline->SetLocationAtSplinePoint(1, FVector(105, 0, 0), ESplineCoordinateSpace::Local);
        }
        else
        {
            PneumaticTube->SetActorLocation(BuildVector, false, nullptr, ETeleportType::TeleportPhysics);
            PneumaticTube->Spline->SetLocationAtSplinePoint(1, FVector(105, 0, 0), ESplineCoordinateSpace::Local);
        }
    }
    else
    {
        // TODO Check if the output hopper for example is already set so we don't snap to the other output actors
        auto hopperI = Cast<AHopperInput>(this->Overlap);
        if (hopperI)
        {
            UE_LOG(LogTemp, Warning, TEXT("%s"), *hopperI->GetName());

            PneumaticTube->Spline->SetLocationAtSplinePoint(SplinePoint, hopperI->GetActorLocation(),
                                                            ESplineCoordinateSpace::World, true);
        }
        else
        {
            PneumaticTube->Spline->SetLocationAtSplinePoint(SplinePoint, BuildVector, ESplineCoordinateSpace::World,
                                                            true);
        }
    }
}
