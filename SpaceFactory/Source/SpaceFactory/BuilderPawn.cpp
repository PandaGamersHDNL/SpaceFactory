// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderPawn.h"

// Sets default values
ABuilderPawn::ABuilderPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuilderPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilderPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation((GetActorLocation() + ConsumeMovementInputVector()), true);
}

// Called to bind functionality to input
void ABuilderPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABuilderPawn::MoveForward);
}

void ABuilderPawn::MoveForward(float Scale)
{
	AddMovementInput(FVector((GetWorld()->GetDeltaSeconds()* Speed), 0.0f, 0.0f), Scale);
}

void ABuilderPawn::MoveRight(float Scale)
{
	AddMovementInput(FVector(0.0f, (GetWorld()->GetDeltaSeconds() * Speed), 0.0f), Scale);
}
