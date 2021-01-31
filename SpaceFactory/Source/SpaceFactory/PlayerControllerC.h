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

	//builder
	UFUNCTION(BlueprintImplementableEvent)
		void BuildingMenu(bool IsInBuildingMode);

	void BuildModeActivate();
	//height of the builder pawn
	UPROPERTY(EditDefaultsOnly, Category = "Builder")
	float BuilderHeight = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Builder")
		TSubclassOf<ABuilderPawn> BuildingBp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Builder")
		float BuilderAngle = -30.0f;

	void BuildMachine();
	void RotateMachine(float Scale);

	float MachineRotationSpeed = 5.0f;
	//--------
};


