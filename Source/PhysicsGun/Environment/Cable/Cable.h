// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/SplineComponent.h"
#include "Engine/Classes/Components/SplineMeshComponent.h"
#include "Cable.generated.h"

UCLASS()
class PHYSICSGUN_API ACable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USplineComponent * Spline;

	UPROPERTY(EditAnywhere)
		UStaticMesh * CableMesh;

};
