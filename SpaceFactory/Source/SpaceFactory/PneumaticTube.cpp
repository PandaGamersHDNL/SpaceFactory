// Fill out your copyright notice in the Description page of Project Settings.

#include "PneumaticTube.h"

// Sets default values
APneumaticTube::APneumaticTube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SetRootComponent(Spline);
}

// Called when the game starts or when spawned
void APneumaticTube::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APneumaticTube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
