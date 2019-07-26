// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class PHYSICSGUN_API UTrigger : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrigger();

	UFUNCTION(BlueprintCallable)
		void Trigger(bool value);

	UPROPERTY(BlueprintAssignable, Category = "Something")
		FTriggerDelegate OnTriggerOn;

	UPROPERTY(BlueprintAssignable, Category = "Something")
		FTriggerDelegate OnTriggerOff;

private:
	bool currentState = false;
};
