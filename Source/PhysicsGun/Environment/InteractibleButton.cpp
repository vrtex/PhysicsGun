// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractibleButton.h"
#include "Triggerable.h"

// Sets default values
AInteractibleButton::AInteractibleButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractibleButton::BeginPlay()
{
	Super::BeginPlay();
	
	for(auto actor : TriggerActors)
	{
		ITriggerable * nextTrigger = nullptr;
		nextTrigger = Cast<ITriggerable>(actor);
		if(!nextTrigger)
			continue;

		Triggers.Add(nextTrigger);
	}
}

// Called every frame
void AInteractibleButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AInteractibleButton::Interact_Implementation(AActor * interacting)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
	for(auto t : Triggers)
		t->Execute_Trigger(t->_getUObject(), true);

	return true;
}