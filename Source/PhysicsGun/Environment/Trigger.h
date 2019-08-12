// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggerDelegate, AActor *, Instigator);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class PHYSICSGUN_API UTrigger : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UTrigger();

	UFUNCTION(BlueprintCallable)
		void Trigger(bool value, AActor * Instigator);


	UFUNCTION(BlueprintCallable)
		void SetCurrentState(bool value);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Something")
		FTriggerDelegate OnTriggerOn;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Something")
		FTriggerDelegate OnTriggerOff;

private:
	bool currentState;
};
