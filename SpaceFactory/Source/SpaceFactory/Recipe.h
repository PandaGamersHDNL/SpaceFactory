#pragma once

#include "ItemAmount.h"
#include "Containers/Array.h"
#include "Engine/DataTable.h"
#include "Recipe.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRecipe : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
    /*
    *the machine that will be able to do this recipe
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Recipe)
    TSubclassOf<class AProcessMachine> ProcessMachine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Recipe)
	TArray<FItemAmount> Inputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Recipe)
	FItemAmount Output;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Recipe)
    float CraftTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Recipe)
    FName Description;
    
};