// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerC.h"
#include "BuilderPawn.h"

void APlayerControllerC::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("BuildMode", IE_Pressed, this, &APlayerControllerC::BuildModeActivate);
	UE_LOG(LogTemp, Warning, TEXT("bind activate"));
}

void APlayerControllerC::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = GetPawn();
	FActorSpawnParameters Params;
	Params.Name = TEXT("Builder");
	if (BuildingBp)
	{
		BuilderPawn = GetWorld()->SpawnActor<ABuilderPawn>(BuildingBp.Get(), FVector(0.0f, 0.0f, BuilderHeight), FRotator(0.0f), Params); //FVector(0.0f, 0.0f, BuilderHeight), FRotator(0.0f), Params
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