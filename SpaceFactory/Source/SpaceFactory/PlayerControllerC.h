// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerC.generated.h"

/**
 * 
 */
UCLASS()
class SPACEFACTORY_API APlayerControllerC : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	

	//APlayerControllerC();

	void Tick(float DeltaTime) override;

	bool isInBuildMode = false;
	/*UPROPERTY(BlueprintReadWrite)
	TSubclassOf<AActor> BuildingObject; //TODO change to class machine when machine class defined*/
	UPROPERTY(BlueprintReadWrite)
		AActor* MachineBuilding = nullptr;

};
