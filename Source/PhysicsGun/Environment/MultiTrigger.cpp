// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiTrigger.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values for this component's properties
UMultiTrigger::UMultiTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMultiTrigger::BeginPlay()
{
	Super::BeginPlay();

	// ...

	for(auto & actor : Actors)
	{

		UE_LOG(LogTemp, Warning, TEXT("Got actor: %s"), *actor.triggerOwner->GetName());
		if(!IsValid(actor.triggerOwner))
		{
			UE_LOG(LogTemp, Error, TEXT("Multi trigger on %s has invalid trigger owner: "), *GetOwner()->GetName());
			continue;

		}
		UTrigger * trigger = Cast<UTrigger>(actor.triggerOwner->GetComponentByClass(UTrigger::StaticClass()));
		if(!IsValid(trigger))
		{
			UE_LOG(LogTemp, Error, TEXT("Multi trigger on %s has actor with no triggers: "), *GetOwner()->GetName(), *actor.triggerOwner->GetName());
			continue;
		}

		if(!actor.bNegate)
		{
			trigger->OnTriggerOn.AddDynamic(this, &UMultiTrigger::RegisterActor);
			trigger->OnTriggerOff.AddDynamic(this, &UMultiTrigger::UnregisterActor);
		}
		else
		{
			trigger->OnTriggerOff.AddDynamic(this, &UMultiTrigger::RegisterActor);
			trigger->OnTriggerOn.AddDynamic(this, &UMultiTrigger::UnregisterActor);
		}

		if(actor.bActiveAtStart && !actor.bNegate)
			currentActors.Add(actor.triggerOwner);
		else if(!actor.bActiveAtStart && actor.bNegate)
			currentActors.Add(actor.triggerOwner);


	}
	PrintCurrent();
}

void UMultiTrigger::RegisterActor(AActor * actor)
{
	if(currentActors.Contains(actor))
	{
		UE_LOG(LogTemp, Error, TEXT("Multi trigger error, UMultiTrigger::RegisterActor"));
		return;
	}


	currentActors.AddUnique(actor);
	if(currentActors.Num() == Actors.Num())
		Trigger(true, actor);

	UE_LOG(LogTemp, Warning, TEXT("adding: %s to: %s"), *actor->GetName(), *GetOwner()->GetName());
	PrintCurrent();
}

void UMultiTrigger::UnregisterActor(AActor * actor)
{

	if(!currentActors.Contains(actor))
	{
		UE_LOG(LogTemp, Error, TEXT("Multi trigger error on: %s, UMultiTrigger::UnregisterActor, %s"), *GetOwner()->GetName(), *actor->GetName());
		return;
	}

	currentActors.Remove(actor);
	if(currentActors.Num() == Actors.Num() - 1)
		Trigger(false, actor);

	
	UE_LOG(LogTemp, Warning, TEXT("removing: %s from: %s"), *actor->GetName(), *GetOwner()->GetName());
	PrintCurrent();
}

void UMultiTrigger::PrintCurrent()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: current actors:-------------"), *GetOwner()->GetName());

	for(auto a : currentActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *a->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("---------"));
}