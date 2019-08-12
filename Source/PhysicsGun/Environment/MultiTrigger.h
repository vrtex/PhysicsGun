// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Trigger.h"
#include "MultiTrigger.generated.h"

USTRUCT(BlueprintType)
struct FTriggerActorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		AActor * triggerOwner = nullptr;
	UPROPERTY(EditAnywhere)
		bool bActiveAtStart = false;
	UPROPERTY(EditAnywhere)
		bool bNegate = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHYSICSGUN_API UMultiTrigger : public UTrigger
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMultiTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FTriggerActorInfo> Actors;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool currentStatus = false;


	TArray<AActor *> currentActors;

public:

	 UFUNCTION()
		void RegisterActor(AActor * actor);

	 UFUNCTION()
		void UnregisterActor(AActor * actor);

private:

	void PrintCurrent();
};
