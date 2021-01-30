// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerC.generated.h"

/**
 * 
 */

class ABuilderPawn;

UCLASS()
class SPACEFACTORY_API APlayerControllerC : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	

	//APlayerControllerC();

	void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	bool isInBuildMode = false;
	
	//height of the new building
	UPROPERTY(EditAnywhere)
		float BuildHeight = 100.0f;

	UPROPERTY(BlueprintReadWrite)
		AActor* MachineBuilding = nullptr;

	void SetupInputComponent();
	void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
		APawn* PlayerPawn;

	UPROPERTY(BlueprintReadWrite)
		ABuilderPawn* BuilderPawn;

	//height of the builder pawn
	float BuilderHeight = 500.0f;

	UFUNCTION(BlueprintImplementableEvent)
		void BuildingMenu(bool IsInBuildingMode);

	void BuildModeActivate();

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABuilderPawn> BuildingBp = nullptr;
};
