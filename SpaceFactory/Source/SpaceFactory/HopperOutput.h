// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineIO.h"
#include "HopperOutput.generated.h"

class APneumaticTube;

UCLASS()
class SPACEFACTORY_API AHopperOutput : public AMachineIO
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHopperOutput();

	//the value where it is concidered at the end of the tube
	UPROPERTY(EditAnywhere)
		float endDistance = 25.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OutputItem();
	bool BuildSelf(class ADetectorBuildTool *BuildTool) override;
};
