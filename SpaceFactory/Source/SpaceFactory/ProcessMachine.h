// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Machine.h"
#include "ProcessMachine.generated.h"

/**
 * 
 */
UCLASS()
class SPACEFACTORY_API AProcessMachine : public AMachine
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class AHopperOutput *HopperOutput;

	UPROPERTY(EditAnywhere)
	class AHopperInput *HopperInput; //TODO multiple inputs

	
};
