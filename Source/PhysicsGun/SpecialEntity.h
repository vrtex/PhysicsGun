// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpecialEntity.generated.h"

UCLASS()
class PHYSICSGUN_API ASpecialEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpecialEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Setup(const class UPrimitiveComponent * comp, FVector location);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
