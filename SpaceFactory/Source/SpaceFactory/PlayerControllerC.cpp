// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerC.h"
#include "PneumaticTube.h"
#include "BuilderPawn.h"

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

	auto PneumaticTube = Cast<APneumaticTube>(MachineBuilding);
	if (isInBuildMode)
	{
		if (PneumaticTube)
		{
			if (SplinePoint == 0)
			{
				float MouseX, MouseY;
				FVector Dir, Pos;
				GetMousePosition(MouseX, MouseY);
				if (DeprojectScreenPositionToWorld(MouseX, MouseY, Pos, Dir))
				{
					PneumaticTube->SetActorLocation((Pos + (((BuildHeight - Pos.Z) / Dir.Z) * Dir)), false);
				}
			}
			else
			{
				float MouseX, MouseY;
				FVector Dir, Pos;
				GetMousePosition(MouseX, MouseY);
				if (DeprojectScreenPositionToWorld(MouseX, MouseY, Pos, Dir))
				{
					PneumaticTube->Spline->SetLocationAtSplinePoint(SplinePoint, (Pos + (((BuildHeight - Pos.Z) / Dir.Z) * Dir)), ESplineCoordinateSpace::World, true);
				}
			}
		}
		else if (MachineBuilding)
		{
			float MouseX, MouseY;
			FVector Dir, Pos;
			GetMousePosition(MouseX, MouseY);
			if (DeprojectScreenPositionToWorld(MouseX, MouseY, Pos, Dir))
			{
				MachineBuilding->SetActorLocation((Pos + (((BuildHeight - Pos.Z) / Dir.Z) * Dir)), false);
			}
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
			UE_LOG(LogTemp, Warning, TEXT("Possesed builderpawn"));
		}
		else
		{
			Possess(PlayerPawn);
			SetShowMouseCursor(false);
			UE_LOG(LogTemp, Warning, TEXT("Possesed player"));
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
			
		}
		else
		{
		}
		SplinePoint++;
		PneumaticTube->Spline->AddSplinePoint(FVector(0.0f),ESplineCoordinateSpace::World, true); //TODO check if the overlap is true if so don't add and stop building :D

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
