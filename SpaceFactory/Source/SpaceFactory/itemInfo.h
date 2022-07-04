// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TiersEnum.h"
#include "itemInfo.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class AItem> Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int PriceBuy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int PriceSell;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETiers tiers;
};
