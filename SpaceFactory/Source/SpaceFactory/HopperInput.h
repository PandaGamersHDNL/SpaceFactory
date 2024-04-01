// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineIO.h"
#include "HopperInput.generated.h"

/**
 *
 */
UCLASS()
class SPACEFACTORY_API AHopperInput : public AMachineIO
{
    GENERATED_BODY()

  public:
    void InputItem();
    bool BuildSelf(class ADetectorBuildTool *BuildTool) override;
};
