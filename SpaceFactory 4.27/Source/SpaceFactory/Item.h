// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "TiersEnum.h"
#include "Item.generated.h"

UCLASS()
class SPACEFACTORY_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Parameters")
		UStaticMeshComponent* ItemCapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		UStaticMeshComponent* ItemInCapsule;

	UStaticMesh* ItemCapsuleMesh = nullptr;
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int Amount = 1;

	//key used for database
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemKey = FName(TEXT("default"));
};
