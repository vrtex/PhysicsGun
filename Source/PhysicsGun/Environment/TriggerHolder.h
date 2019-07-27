// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TriggerHolder.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class PHYSICSGUN_API UTriggerHolder : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerHolder();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
		void UseTriggers(bool value, AActor * User);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<AActor *> TriggerActors;

private:
	TArray<class UTrigger*> Triggers;
};
