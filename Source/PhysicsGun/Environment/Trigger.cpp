// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values for this component's properties
UTrigger::UTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UTrigger::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto triggers = GetOwner()->GetComponentsByClass(UTrigger::StaticClass());
	if(triggers.Num() != 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Multiple triggers on %s"), *GetOwner()->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("Value: %d, owner: %s"), (int)currentState, *GetOwner()->GetName());
}


void UTrigger::Trigger(bool value, AActor * Instigator)
{
	if(currentState == value)
	{
		UE_LOG(LogTemp, Warning, TEXT("lol, value: %d"), (int)value);
		return;
	}

	currentState = value;

	if(currentState)
		OnTriggerOn.Broadcast(Instigator);
	else
		OnTriggerOff.Broadcast(Instigator);
}

void UTrigger::SetCurrentState(bool value)
{
	UE_LOG(LogTemp, Warning, TEXT("setting value: %d"), (int)value);
	currentState = value;
}