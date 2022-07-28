// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Machine.generated.h"

enum Tiers
{
    Tier0,
    Tier1
};

class AItem;
class APlayerControllerC;

UCLASS()
class SPACEFACTORY_API AMachine : public AActor
{
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    AMachine();

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    AItem *OutputItem = nullptr; // output no buffer
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AItem *InputItem = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APlayerControllerC *OwnerController = nullptr;

    virtual bool BuildSelf(class ADetectorBuildTool *BuildTool);

    //TODO make function that moves the machine (basic is set actor/ ex pneumatic tube is different)
    // TODO open ui when user clicks on building, ore when interacting as player (not builder)
    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> ui;
};
