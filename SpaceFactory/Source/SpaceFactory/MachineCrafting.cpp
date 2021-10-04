// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "MachineCrafting.h"

void AMachineCrafting::BeginPlay()
{
    Super::BeginPlay();
    setRecipe(KeyRecipe);
}

void AMachineCrafting::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    InputToList();
    Craft();
}

void AMachineCrafting::setRecipe(FName row)
{
    Recipe = RecipesDT->FindRow<FRecipe>(row, "MachineCraftingRecipeDT", true);
    //UE_LOG(LogTemp, Display, TEXT("%s"), *Recipe->Inputs);
    ItemList.Empty();
    for (FItemAmount Input : Recipe->Inputs)
    {
        Input.Amount = 0;
        ItemList.Add(Input);
    }
    UE_LOG(LogTemp, Warning, TEXT("%d + %d"), ItemList.Num(), Recipe->Inputs.Num());
}

void AMachineCrafting::Craft()
{
    //ptr prot + cooldown
    if (!Recipe || !Recipe->CraftTime || GetWorldTimerManager().GetTimerRemaining(Cooldown) > 0.1f)
        return;
    if (CheckItemAmounts() && !OutputItem)
    {
        RemoveItemAmounts();
        FActorSpawnParameters Params;
        OutputItem = GetWorld()->SpawnActor<AItem>(Recipe->Output.Item.Get(), FVector(GetActorLocation()), FRotator(GetActorRotation()), Params);
        OutputItem->Amount = Recipe->Output.Amount;
        //WARN if spawning would fail it might crash the game

        UE_LOG(LogTemp, Warning, TEXT("craft ready"));
    }
    UE_LOG(LogTemp, Warning, TEXT("%s used craft()"), *this->GetFName().ToString());
    GetWorldTimerManager().SetTimer(Cooldown, this, &AMachineCrafting::Craft, 10.0f, false, Recipe->CraftTime);
}

void AMachineCrafting::InputToList()
{
    if (!InputItem)
        return;
    //item iterator
    for (auto ItemIt = ItemList.CreateIterator(); ItemIt; ItemIt++)
    {
        if (ItemIt->Item.Get() == InputItem->GetClass())
        {
            if (ItemIt->Amount < Recipe->Inputs[ItemIt.GetIndex()].Amount * BufferMultiplier)
            {
                ItemIt->Amount += InputItem->Amount;
                if (InputItem->Destroy())
                {
                    InputItem = nullptr;
                }
            }
            //UE_LOG(LogTemp, Warning, TEXT("Your message %s %s"), *InputItem->GetClass()->GetDisplayNameText().ToString(), *Input.Item.Get()->GetDisplayNameText().ToString());
        }
    }
}

bool AMachineCrafting::CheckItemAmounts()
{
    for (auto ItemIt = ItemList.CreateIterator(); ItemIt; ItemIt++)
    {
        if (ItemIt->Amount < Recipe->Inputs[ItemIt.GetIndex()].Amount)
        {
            return false;
        }
    }
    return true;
}

void AMachineCrafting::RemoveItemAmounts()
{
    for (auto ItemIt = ItemList.CreateIterator(); ItemIt; ItemIt++)
    {
        ItemIt->Amount -= Recipe->Inputs[ItemIt.GetIndex()].Amount;
    }
}