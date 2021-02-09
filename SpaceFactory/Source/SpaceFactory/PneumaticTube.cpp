// Fill out your copyright notice in the Description page of Project Settings.

#include "PneumaticTube.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
APneumaticTube::APneumaticTube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SceneComponent->SetMobility(EComponentMobility::Static);*/

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->AddSplinePoint(FVector(0.0f), ESplineCoordinateSpace::Local, true);
	Spline->SetMobility(EComponentMobility::Movable);
	//Spline->SetupAttachment(RootComponent);
	RootComponent = Spline;
	Spline->bDrawDebug = true;
	Spline->SetVisibility(true);

	bGenerateOverlapEventsDuringLevelStreaming = true;
	
	//Mesh = CreateDefaultSubobject<USplineMeshComponent>(TEXT("Mesh"));
	/*Mesh->SetupAttachment(SceneComponent);
	Mesh->SetRelativeLocation(FVector(0.0f));
	Mesh->SetRelativeScale3D(FVector(0.0f));*/
	

	UE_LOG(LogTemp, Warning, TEXT("constructor ran"));
}

// Called when the game starts or when spawned
void APneumaticTube::BeginPlay()
{
	Super::BeginPlay();
	//OnActorBeginOverlap.AddDynamic(this, &APneumaticTube::OnBeginOverlap);
	Spline->OnComponentBeginOverlap.AddDynamic(this, &APneumaticTube::OnBeginOverlap);
	//OnActorBeginOverlap.DynamicAdd(this, APneumaticTube::OnOverlap)
}


// Called every frame
void APneumaticTube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APneumaticTube::OnBeginOverlap( UPrimitiveComponent* OverlapComponent,  AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("begin overlap"));
}
