// Fill out your copyright notice in the Description page of Project Settings.

#include "PneumaticTube.h"
#include "Item.h"
#include "Components/SplineMeshComponent.h"
#include "HopperInput.h"
#include "HopperOutput.h"

// Sets default values
APneumaticTube::APneumaticTube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SceneComponent->SetMobility(EComponentMobility::Static);*/

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetMobility(EComponentMobility::Movable);
	Spline->SetLocationAtSplinePoint(0, FVector(0.0f), ESplineCoordinateSpace::Local, true);
	Spline->SetLocationAtSplinePoint(1, FVector(10.0f, 0.0f, 0.0f), ESplineCoordinateSpace::Local, true);
	UE_LOG(LogTemp, Warning, TEXT("%i"), Spline->GetNumberOfSplinePoints());
	RootComponent = Spline;
	Spline->bDrawDebug = true;
	Spline->SetVisibility(true);
	bGenerateOverlapEventsDuringLevelStreaming = true;
}

// Called when the game starts or when spawned
void APneumaticTube::BeginPlay()
{
	Super::BeginPlay();
	Spline->OnComponentBeginOverlap.AddDynamic(this, &APneumaticTube::OnBeginOverlap);
}

// Called every frame
void APneumaticTube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveItem(DeltaTime);
}

void APneumaticTube::OnBeginOverlap(UPrimitiveComponent *OverlapComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("begin overlap"));
}

void APneumaticTube::MoveItem(float DeltaTime)
{
	if (!TransportingItem)
	{
		return;
	}
	ItemDistance += (DeltaTime * TransportSpeed);
	TransportingItem->SetActorLocation(Spline->GetLocationAtDistanceAlongSpline(ItemDistance, ESplineCoordinateSpace::World), false);
	FRotator rotation = Spline->GetRotationAtDistanceAlongSpline(ItemDistance, ESplineCoordinateSpace::Local);
	//UE_LOG(LogTemp, Warning, TEXT("rotation at item distance %s"), *rotation.ToString());
	TransportingItem->SetActorRotation(rotation);

	if (Spline->GetSplineLength() - 10.0f < ItemDistance) //TODO make 10.0f var for editor
	{
		//put in input hopper?
		TransportingItem->SetActorLocation(Spline->GetLocationAtDistanceAlongSpline(Spline->GetSplineLength(), ESplineCoordinateSpace::World), false);
		if (HopperInput)
		{
			HopperInput->InputItem();
		}
		//call the inputhopper to add to input
	}
}