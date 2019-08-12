// Fill out your copyright notice in the Description page of Project Settings.

#include "Cable.h"
#include <string>

// Sets default values
ACable::ACable()
{
	PrimaryActorTick.bCanEverTick = false;


	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SetRootComponent(Spline);


	for(int i = 0; i < Spline->GetNumberOfSplinePoints() - 2; ++i)
	{
		// USplineMeshComponent * newMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		std::string name = "mesh";
		name += std::to_string(i);
		USplineMeshComponent * newMesh = CreateDefaultSubobject<USplineMeshComponent>(FName(*FString(name.c_str())));
		newMesh->SetupAttachment(GetRootComponent());

		FVector startLocation, startTangent;
		FVector endLocation, endTangent;
		Spline->GetLocationAndTangentAtSplinePoint(i, startLocation, startTangent, ESplineCoordinateSpace::Local);
		Spline->GetLocationAndTangentAtSplinePoint(i + 1, endLocation, endTangent, ESplineCoordinateSpace::Local);

		newMesh->SetStartAndEnd(startLocation, startTangent, endLocation, endTangent);
		newMesh->SetStaticMesh(CableMesh);
		// newMesh->RegisterComponent();
	}


	UE_LOG(LogTemp, Warning, TEXT("Comps: %d"), GetComponents().Num());
}

// Called when the game starts or when spawned
void ACable::BeginPlay()
{
	Super::BeginPlay();
	

}


