// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectorBuildTool.h"
#include "PlayerControllerC.h"
#include "HopperInput.h"
#include "HopperOutput.h"


// Sets default values
ADetectorBuildTool::ADetectorBuildTool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetRelativeScale3D(FVector(0.1f));
	Mesh->SetVisibility(false, true);
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ADetectorBuildTool::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ADetectorBuildTool::BeginOverlap);
	Mesh->OnComponentEndOverlap.AddDynamic(this, &ADetectorBuildTool::EndOverlap);
	//bGenerateOverlapEventsDuringLevelStreaming = true;
}

// Called every frame
void ADetectorBuildTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADetectorBuildTool::BeginOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("begin: %s"), *OtherActor->GetName());
	if (Cast<AHopperInput>(OtherActor) && PlayerController->bHopperInput == false)
	{
		PlayerController->HopperInput = Cast<AHopperInput>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Input hopper set to %s"), *OtherActor->GetName());
	}
	else if (Cast<AHopperOutput>(OtherActor) && PlayerController->bHopperOutput == false)
	{
		PlayerController->HopperOutput = Cast<AHopperOutput>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Output hopper set to %s"), *OtherActor->GetName());
	}
}

void ADetectorBuildTool::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("End: %s"), *OtherActor->GetName());
	if (OtherActor == PlayerController->HopperInput && PlayerController->bHopperInput == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input hopper set to null: %s"), *OtherActor->GetName());
		PlayerController->HopperInput = nullptr;
	}
	else if (OtherActor == PlayerController->HopperOutput && PlayerController->bHopperOutput == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Output hopper set to null: %s"), *OtherActor->GetName());
		PlayerController->HopperOutput = nullptr;
	}
}