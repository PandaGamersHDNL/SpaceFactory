// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerC.h"

#include "BuilderPawn.h"
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
				PneumaticTube->SetActorLocation((Pos + (((BuildHeight - Pos.Z) / Dir.Z) * Dir)), false);
				//UE_LOG(LogTemp, Warning, TEXT("%s sp 0"), *FVector((Pos + (((BuildHeight - Pos.Z) / Dir.Z) * Dir))).ToString());
			}
			else
			{
				FVector Vector = FVector((Pos + ((BuildHeight - Pos.Z) / Dir.Z) * Dir));
				PneumaticTube->Spline->SetLocationAtSplinePoint(SplinePoint, Vector, ESplineCoordinateSpace::World, true);
				//UE_LOG(LogTemp, Warning, TEXT("%s"), *Vector.ToString());
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
				DetectorBT->SetHidden(true);
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
		if (SplinePoint == 0)
		{
			//check what it is Input or output, set the var in the tube
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
