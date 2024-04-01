// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemAmount.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemAmount
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Recipe)
    FName ItemDisplayName = FName(TEXT("default"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemAmount)
	TSubclassOf<class AItem> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemAmount)
	int Amount = 1;
};