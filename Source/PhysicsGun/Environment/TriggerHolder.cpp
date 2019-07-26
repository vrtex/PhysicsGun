// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerHolder.h"
#include "Environment/Trigger.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values for this component's properties
UTriggerHolder::UTriggerHolder()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...


}


// Called when the game starts
void UTriggerHolder::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for(auto actor : TriggerActors)
	{
		UTrigger * nextTrigger = nullptr;
		nextTrigger = Cast<UTrigger>(actor->GetComponentByClass(UTrigger::StaticClass()));
		if(!IsValid(nextTrigger))
			continue;

		Triggers.Add(nextTrigger);
	}

	
}

void UTriggerHolder::UseTriggers(bool value)
{
	for(auto t : Triggers)
	{
		if(!IsValid(t))
			continue;
		t->Trigger(value);
	}
}