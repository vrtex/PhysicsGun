// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "InteractibleButton.generated.h"

class ITriggerable;

UCLASS()
class PHYSICSGUN_API AInteractibleButton : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractibleButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interaction)
		bool Interact(AActor * interacting);
	bool Interact_Implementation(AActor * interacting) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor *> TriggerActors;

private:
		TArray<ITriggerable *> Triggers;

	
};
