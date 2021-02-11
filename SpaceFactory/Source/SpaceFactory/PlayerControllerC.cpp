// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerC.h"

#include "BuilderPawn.h"
#include "HopperInput.h"
#include "HopperOutput.h"
#include "DetectorBuildTool.h"
#include "PneumaticTube.h"

void APlayerControllerC::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("BuildMode", IE_Pressed, this, &APlayerControllerC::BuildModeActivate);
	//move to builder pawn maybe
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
		//SetControlRotation(FRotator(0.0f));
		BuilderPawn = GetWorld()->SpawnActor<ABuilderPawn>(BuildingBp.Get(), FVector(0.0f, 0.0f, BuilderHeight), FRotator(BuilderAngle, 0.0f, 0.0f), Params);
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
		if (DetectorBT)
		{
			DetectorBT->SetActorLocation((Pos + (((BuildHeight - Pos.Z) / Dir.Z) * Dir)), false);
			//UE_LOG(LogTemp, Warning, TEXT("set loc detector 1"));
		}
		auto PneumaticTube = Cast<APneumaticTube>(MachineBuilding);
		if (PneumaticTube)
		{
			if (SplinePoint == 0)
			{
				if (HopperOutput)
					PneumaticTube->SetActorLocation(HopperOutput->GetActorLocation());
				else if (HopperInput)
					PneumaticTube->SetActorLocation(HopperInput->GetActorLocation());
				else
					PneumaticTube->SetActorLocation((Pos + (((BuildHeight - Pos.Z) / Dir.Z) * Dir)), false);
			}
			else
			{
				//TODO Check if the output hopper for example is already set so we don't snap to the other output actors
				if (HopperOutput)
					PneumaticTube->Spline->SetLocationAtSplinePoint(SplinePoint, HopperOutput->GetActorLocation(), ESplineCoordinateSpace::World, true);
				else if (HopperInput)
					PneumaticTube->Spline->SetLocationAtSplinePoint(SplinePoint, HopperInput->GetActorLocation(), ESplineCoordinateSpace::World, true);
				else
					PneumaticTube->Spline->SetLocationAtSplinePoint(SplinePoint, (Pos + ((BuildHeight - Pos.Z) / Dir.Z) * Dir), ESplineCoordinateSpace::World, true);
			}
		}
		else if (MachineBuilding)
		{

			MachineBuilding->SetActorLocation((Pos + (((BuildHeight - Pos.Z) / Dir.Z) * Dir)), false);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FVector((Pos + (((BuildHeight - Pos.Z) / Dir.Z) * Dir))).ToString());

		}
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
				DetectorBT = GetWorld()->SpawnActor<ADetectorBuildTool>(DetectorBTBP.Get(), FVector(0.0f, 0.0f, BuilderHeight), FRotator(BuilderAngle, 0.0f, 0.0f), Params);
				//DetectorBT->SetHidden(true);
				DetectorBT->PlayerController = this;
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
	auto PneumaticTube = Cast<APneumaticTube>(MachineBuilding);
	if (PneumaticTube)
	{
		if (bOutputHFirst ) // make this to int so you have a start  state and a decion state  -> 0 not defined 1 output first 2 input first ->ENUM?
		{
			if (HopperOutput)
			{
				if (SplinePoint == 0)
				{
					bHopperOutput = true;
					//stop setting location of pneaumatic tube spline point instead // might already happen in TICK
					//set it to the location of the output hopper also tangent from dir of hopper "ARROW"
				}
				else
				{
					if (HopperInput)
					{
						//set the machine building to nullptr
						//set location of spline point to Hopper input Location
						//set all the references inside of the pneaumatic tube and hoppers
					}
					else
					{
						SplinePoint++;
						PneumaticTube->Spline->AddSplinePoint(FVector(0.0f), ESplineCoordinateSpace::World, true);
					}
				}
			}
		}
		else
		{
			if (HopperInput)
			{
				if (SplinePoint == 0)
				{
					//stop setting location of pneaumatic tube spline point instead // might already happen in TICK
					//set it to the location of the output hopper also tangent from dir of hopper "ARROW"
				}
				else
				{
					if (HopperOutput)
					{
						//set the machine building to nullptr
						//set location of spline point to Hopper input Location
						//set all the references inside of the pneaumatic tube and hoppers
					}
					else
					{
						SplinePoint++;
						PneumaticTube->Spline->AddSplinePoint(FVector(0.0f), ESplineCoordinateSpace::World, true);
					}
				}
			}
		}
		SplinePoint++;
		PneumaticTube->Spline->AddSplinePoint(FVector(0.0f), ESplineCoordinateSpace::World, true); //TODO check if the overlap is true if so don't add and stop building :D
																								  //Then get the tangent and set it for the last point
	}
	else if (MachineBuilding)
	{
		MachineBuilding = nullptr;
	}
}

void APlayerControllerC::RotateMachine(float Scale)
{
	if (MachineBuilding)
	{
		MachineBuilding->SetActorRotation(FRotator(0.0f, MachineBuilding->GetActorRotation().Yaw + (MachineRotationSpeed * Scale), 0.0f));
	}
}
