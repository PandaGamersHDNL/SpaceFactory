// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Machine.h"
#include "HopperOutput.generated.h"

UCLASS()
class SPACEFACTORY_API AHopperOutput : public AMachine
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHopperOutput();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
