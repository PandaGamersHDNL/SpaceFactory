// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "ItemAmount.h"
#include "ProcessMachine.h"
#include "Recipe.h"

#include "MachineCrafting.generated.h"

/**
 *
 */
UCLASS()
class SPACEFACTORY_API AMachineCrafting : public AProcessMachine
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditAnywhere)
    class UDataTable *RecipesDT = nullptr;

    UFUNCTION()
    void Craft();

    void InputToList();

    UFUNCTION(BlueprintCallable)
    void setRecipe(FName row);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName KeyRecipe = FName(TEXT("IronIngotToPlate"));

    UPROPERTY(EditAnywhere)
    TArray<FItemAmount> ItemList;

    UPROPERTY(EditAnywhere)
    float BufferMultiplier = 5.0f;

    bool CheckItemAmounts();
    void RemoveItemAmounts();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual bool BuildSelf(class ADetectorBuildTool *Detector) override;

  private:
    FRecipe *Recipe;
    FTimerHandle Cooldown;
};
