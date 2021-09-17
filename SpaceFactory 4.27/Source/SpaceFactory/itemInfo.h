// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "TiersEnum.h"
#include "Engine/DataTable.h"
#include "itemInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	TSubclassOf<class AItem> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	int PriceBuy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	int PriceSell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyCategory)
	ETiers tiers;
};
/*
UCLASS(Blueprintable)
class SPACEFACTORY_API UitemInfo : public UUserDefinedStruct
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MyCategory)
		TSubclassOf<class AItem> Item;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MyCategory)
		int PriceBuy;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MyCategory)
		int PriceSell;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MyCategory)
		class ETiers tiers;
};*/
