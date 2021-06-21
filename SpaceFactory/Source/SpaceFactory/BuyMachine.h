// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcessMachine.h"
#include "BuyMachine.generated.h"

/**
 * 
 */
UCLASS()
class SPACEFACTORY_API ABuyMachine : public AProcessMachine
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItem> SpawnClass;

	UPROPERTY(EditAnywhere)
	class AItem *SpawnedItem;

	virtual void BeginPlay() override;

	void SpawnItem();

	FTimerHandle TimerHandle;
	void StartTimer();
};
