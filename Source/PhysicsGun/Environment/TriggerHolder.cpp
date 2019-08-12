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
	for(auto & actor : TriggerActors)
	{
		if(!IsValid(actor.triggerOwner))
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid actor in trigger holder, %s"), *GetOwner()->GetName());
			continue;
		}
		UTrigger * nextTrigger = nullptr;
		nextTrigger = Cast<UTrigger>(actor.triggerOwner->GetComponentByClass(UTrigger::StaticClass()));
		if(!IsValid(nextTrigger))
			continue;

		actor.trigger = nextTrigger;
		Triggers.Add(nextTrigger);
	}

	
}

void UTriggerHolder::UseTriggers(bool value, AActor * user)
{
	/*
	for(auto t : Triggers)
	{
		if(!IsValid(t))
			continue;
		t->Trigger(value, user);
	}
	*/

	for(auto & t : TriggerActors)
	{
		if(!IsValid(t.trigger))
			continue;
		t.trigger->Trigger(t.bNegate ? !value : value , user);
	}
}