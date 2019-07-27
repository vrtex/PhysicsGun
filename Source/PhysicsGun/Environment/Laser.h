// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class PHYSICSGUN_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser();

	UPROPERTY(VisibleDefaultsOnly, Category = Setup)
		class USceneComponent * Start;


	UPROPERTY(VisibleDefaultsOnly, Category = Setup)
		class USceneComponent * End;

	UPROPERTY(VisibleDefaultsOnly, Category = Setup)
		class USceneComponent * BlockingPoint;

	UPROPERTY(VisibleDefaultsOnly, Category = Setup)
		class UTrigger * Trigger;

	UPROPERTY(VisibleDefaultsOnly, Category = Setup)
		class UTriggerHolder * TriggerHolder;

	UPROPERTY(VisibleDefaultsOnly, Category = Setup)
		class UCableComponent * Beam;

	UPROPERTY(EditAnywhere, Category = Beam)
		bool On = true;

	UPROPERTY(VisibleAnywhere, Category = Beam)
		bool Connected = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
		void TriggerOn(AActor * User);
	UFUNCTION()
		void TriggerOff(AActor * User);


	void UpdateLaser(bool newValue);

	void Connect();

	void Block();

	bool TraceLaser();

};
