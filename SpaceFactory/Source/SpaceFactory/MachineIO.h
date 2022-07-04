// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Machine.h"
#include "MachineIO.generated.h"

/**
 *
 */
UCLASS()
class SPACEFACTORY_API AMachineIO : public AMachine
{
    GENERATED_BODY()
  protected:
    UPROPERTY(EditAnywhere)
    float DetectDistance = 150.0f;

  public:
    UPROPERTY(EditAnywhere, Category = "Dynamic setup")
    class AProcessMachine *Machine = nullptr;
    UPROPERTY(EditAnywhere, Category = "Dynamic setup")
    class APneumaticTube *PneumaticTube = nullptr;
};
