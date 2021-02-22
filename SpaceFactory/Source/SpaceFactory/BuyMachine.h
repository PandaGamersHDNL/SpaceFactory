// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Machine.h"
#include "BuyMachine.generated.h"

/**
 * 
 */
UCLASS()
class SPACEFACTORY_API ABuyMachine : public AMachine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		class AHopperOutput* HopperOutput;
};
