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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* Spline;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		//void OnBeginOverlap(UPrimitiveComponent* OverlappedComp , AActor* Overlapped, AActor* Other, int32 BodyIndex, bool bSweep, FHitResult& SweepResult );
		void OnBeginOverlap(class UPrimitiveComponent* OverlapComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(VisibleAnywhere)
	class USplineMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
