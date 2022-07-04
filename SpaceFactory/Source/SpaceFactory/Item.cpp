// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "UObject/ConstructorHelpers.h"

#define ItemCapsulePATH "StaticMesh'/Game/Items/capsule.capsule'"

// Sets default values
AItem::AItem()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    ItemCapsuleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemCapsule"));

    RootComponent = ItemCapsuleComponent;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemCapsule(TEXT(ItemCapsulePATH));

    if (ItemCapsule.Succeeded())
    {
        ItemCapsuleMesh = ItemCapsule.Object;
        ItemCapsuleComponent->SetStaticMesh(ItemCapsuleMesh);
    }

    // static ConstructorHelpers::FObjectFinder<U

    ItemInCapsule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
    ItemInCapsule->SetupAttachment(RootComponent);
    SetActorScale3D(FVector(.15f));
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
