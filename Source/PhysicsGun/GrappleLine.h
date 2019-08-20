// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnginePropertySpecifiers.h"
#include "GrappleLine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHYSICSGUN_API UGrappleLine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrappleLine();

public:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnActivated(UActorComponent* Component, bool bReset);
	UFUNCTION()
		void OnDeactivated(UActorComponent* Component);
	UFUNCTION(BlueprintCallable)
		void SetTarget(AActor * NewTarget);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float PullingSpeed = 100.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float DistanceTolerance = 100.f;


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float SmoothingDistance = 1000.f;

private:
	class APhysicsGunCharacter * ControlledCharacter;
	AActor * CurrentTarget;
		
};
