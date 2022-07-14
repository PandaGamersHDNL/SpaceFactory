// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerC.generated.h"
// maybe
/**UENUM()
enum BuildingType
{
    Machine UMETA(DisplayName = "Machine"),
    PneumaticTube UMETA(DisplayName = "Pneumatic tube")
    // InputOutput UMETA(DisplayName = "Input/Output"),
};


 *
 */

class ABuilderPawn;
class APneumaticTube;

UCLASS()
class SPACEFACTORY_API APlayerControllerC : public APlayerController
{
    GENERATED_BODY()

  public:
    // APlayerControllerC();

    void Tick(float DeltaTime) override;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int Money = 100;

    UPROPERTY(BlueprintReadWrite)
    bool isInBuildMode = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    class AMachine *MachineBuilding = nullptr;

    void SetupInputComponent();
    void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite)
    APawn *PlayerPawn = nullptr;

    UPROPERTY(BlueprintReadWrite)
    ABuilderPawn *BuilderPawn = nullptr;

    // builder
    UFUNCTION(BlueprintImplementableEvent)
    void BuildingMenu(bool IsInBuildingMode);

    // height of the new building
    UPROPERTY(EditAnywhere, Category = "Builder")
    float BuildHeight = 100.0f;

    void BuildModeActivate();
    // height of the builder pawn
    UPROPERTY(EditDefaultsOnly, Category = "Builder")
    float BuilderHeight = 500.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Builder")
    TSubclassOf<ABuilderPawn> BuildingBp = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Builder")
    float BuilderAngle = -30.0f;

    void BuildMachine();
    void RotateMachine(float Scale);
    UFUNCTION(BlueprintCallable)
    void CreateMachine(TSubclassOf<AMachine> MachineClass);

    float MachineRotationSpeed = 5.0f;

    int SplinePoint = 0;

    UPROPERTY(BlueprintReadWrite)
    class ADetectorBuildTool *DetectorBT;
    AMachine* Overlap = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Builder")
    TSubclassOf<class ADetectorBuildTool> DetectorBTBP = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Builder")
    float TangentSize = 1000.0f;

    UPROPERTY(EditDefaultsOnly)
    float SecondSplinePointDistance = 100.0f;
    //--------

    void MoveSplinePoint(APneumaticTube *PneumaticTube, FVector BuildVector);
};
