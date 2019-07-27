// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"

// Sets default values for this component's properties
UTrigger::UTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTrigger::Trigger(bool value, AActor * Instigator)
{
	if(currentState == value)
		return;

	currentState = value;

	if(currentState)
		OnTriggerOn.Broadcast(Instigator);
	else
		OnTriggerOff.Broadcast(Instigator);
}