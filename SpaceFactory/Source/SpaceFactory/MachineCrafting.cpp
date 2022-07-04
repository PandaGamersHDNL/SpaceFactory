// Fill out your copyright notice in the Description page of Project Settings.

#include "MachineCrafting.h"
#include "Item.h"

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
    check(RecipesDT)
    Recipe = RecipesDT->FindRow<FRecipe>(row, "MachineCraftingRecipeDT", true);
    ItemList.Empty();
    for (FItemAmount Input : Recipe->Inputs)
    {
        Input.Amount = 0;
        ItemList.Add(Input);
    }
}

void AMachineCrafting::Craft()
{
    // ptr prot + cooldown
    if (!Recipe || !Recipe->CraftTime || GetWorldTimerManager().GetTimerRemaining(Cooldown) > 0.1f)
        return;
    if (CheckItemAmounts() && !OutputItem)
    {
        RemoveItemAmounts();
        FActorSpawnParameters Params;
        OutputItem = GetWorld()->SpawnActor<AItem>(Recipe->Output.Item.Get(), FVector(GetActorLocation()),
                                                   FRotator(GetActorRotation()), Params);
        OutputItem->Amount = Recipe->Output.Amount;
        // WARN if spawning would fail it might crash the game
    }
    GetWorldTimerManager().SetTimer(Cooldown, this, &AMachineCrafting::Craft, 10.0f, false, Recipe->CraftTime);
}

void AMachineCrafting::InputToList()
{
    if (!InputItem)
        return;
    // item iterator
    for (auto ItemIt = ItemList.CreateIterator(); ItemIt; ItemIt++)
    {
        if (ItemIt->Item.Get() == InputItem->GetClass())
        {
            if (ItemIt->Amount < Recipe->Inputs[ItemIt.GetIndex()].Amount * BufferMultiplier)
            {
                ItemIt->Amount += InputItem->Amount;
                if (InputItem->Destroy())
                {
                    UE_LOG(LogTemp, Warning, TEXT("Your message %s %s"),
                           *InputItem->GetClass()->GetDisplayNameText().ToString(),
                           *ItemIt->Item.Get()->GetDisplayNameText().ToString());
                    InputItem = nullptr;
                    return;
                }
            }
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

bool AMachineCrafting::BuildSelf(ADetectorBuildTool *Detector)
{
    UE_LOG(LogTemp, Warning, TEXT("build self machine crafting"));
    return true;
}
