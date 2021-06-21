// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Machine.h"
#include "HopperInput.generated.h"

/**
 * 
 */
UCLASS()
class SPACEFACTORY_API AHopperInput : public AMachine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class AProcessMachine *Machine = nullptr;
	UPROPERTY(EditAnywhere)
	class APneumaticTube *PneumaticTube = nullptr;

	UPROPERTY(EditAnywhere)
	float DetectDistance = 150.0f;

public:
	void InputItem();
	bool BuildSelf(class ADetectorBuildTool *BuildTool);
};
