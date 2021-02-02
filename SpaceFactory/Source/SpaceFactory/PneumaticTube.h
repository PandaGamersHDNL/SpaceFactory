// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "Components/SplineComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "PneumaticTube.generated.h"

UCLASS()
class SPACEFACTORY_API APneumaticTube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APneumaticTube();

	bool OnInputHopper = false;
	bool OnOutputHopper = false; //is input for tube

	UPROPERTY(VisibleAnywhere)
	USplineComponent* Spline;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	UPROPERTY(VisibleAnywhere)
	class USplineMeshComponent* Mesh;


	/*
	UFUNCTION()
		void OnBeginOverlap();
	*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
