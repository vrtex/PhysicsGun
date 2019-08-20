// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsGunProjectile.h"
#include "GrappleLineProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PHYSICSGUN_API AGrappleLineProjectile : public APhysicsGunProjectile
{
	GENERATED_BODY()
	

public:
	virtual void BeginPlay() override;


	void OnHitHandler(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION(BlueprintNativeEvent)
		void Setup(class UGrappleLine * LineComp);
	void Setup_Implementation(class UGrappleLine * LineComp);

	UFUNCTION(BlueprintImplementableEvent)
		void Wait();

	UFUNCTION()
	void OnLineDeactivated(UActorComponent * Comp);

private:
	UGrappleLine * ControlledLine = nullptr;
};
