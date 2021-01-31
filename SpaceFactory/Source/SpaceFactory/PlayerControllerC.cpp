// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerC.h"
#include "BuilderPawn.h"

void APlayerControllerC::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("BuildMode", IE_Pressed, this, &APlayerControllerC::BuildModeActivate);
	InputComponent->BindAction("BuildMachine", IE_Pressed, this, &APlayerControllerC::BuildMachine); //move to builder pawn maybe
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
		SetControlRotation(FRotator(0.0f));
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

	if (isInBuildMode && MachineBuilding)
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
	if (MachineBuilding)
	{
		MachineBuilding = nullptr;
	}
}

void APlayerControllerC::RotateMachine(float Scale)
{
	if (MachineBuilding)
	{
		MachineBuilding->SetActorRotation(FRotator(0.0f, MachineBuilding->GetActorRotation().Yaw + (MachineRotationSpeed * Scale), 0.0f));
		UE_LOG(LogTemp, Warning, TEXT("%f, %s"), Scale, *MachineBuilding->GetName());
	}
}
