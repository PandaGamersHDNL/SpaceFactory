// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SplineComponent.h"
#include "CoreMinimal.h"
#include "Machine.h"

#include "PneumaticTube.generated.h"

UCLASS()
class SPACEFACTORY_API APneumaticTube : public AMachine
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APneumaticTube();

	bool OnInputHopper = false;
	bool OnOutputHopper = false; //is input for tube

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent *Spline;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	//void OnBeginOverlap(UPrimitiveComponent* OverlappedComp , AActor* Overlapped, AActor* Other, int32 BodyIndex, bool bSweep, FHitResult& SweepResult );
	void OnBeginOverlap(class UPrimitiveComponent *OverlapComponent, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UPROPERTY(VisibleAnywhere)
	class USplineMeshComponent *Mesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent *SceneComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Item Transport	only for 1 item per pneumatic tube
	UPROPERTY(EditAnywhere)
	class AItem *TransportingItem;

	void MoveItem(float DeltaTime);

	float ItemDistance = 0.0f;

	UPROPERTY(EditAnywhere) //TODO EditDefaultsOnly
	float TransportSpeed = 200.0f;

		UPROPERTY(EditAnywhere)
	class AHopperOutput *HopperOutput;

	UPROPERTY(EditAnywhere)
	class AHopperInput *HopperInput;
};
