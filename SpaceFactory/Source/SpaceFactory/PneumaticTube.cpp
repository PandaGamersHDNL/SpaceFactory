// Fill out your copyright notice in the Description page of Project Settings.

#include "PneumaticTube.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
APneumaticTube::APneumaticTube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SetRootComponent(Spline);
	Spline->AddSplinePoint(FVector(0.0f), ESplineCoordinateSpace::Local, true);

	Spline->bDrawDebug = true;
	Spline->SetVisibility(true);
	/*Mesh = CreateDefaultSubobject<USplineMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeLocation(FVector(0.0f));*/
	
	UE_LOG(LogTemp, Warning, TEXT("constructor ran"));
}

// Called when the game starts or when spawned
void APneumaticTube::BeginPlay()
{
	Super::BeginPlay();
	//OnActorBeginOverlap.DynamicAdd(this, APneumaticTube::OnOverlap)
}

// Called every frame
void APneumaticTube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}