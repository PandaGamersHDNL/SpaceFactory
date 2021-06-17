// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcessMachine.h"
#include "SellMachine.generated.h"

/**
 * 
 */
UCLASS()
class SPACEFACTORY_API ASellMachine : public AProcessMachine
{
	GENERATED_BODY()

	ASellMachine();
	public:
		virtual void Tick(float DeltaTime) override;
	class AItem* ItemToSell = nullptr;
};
