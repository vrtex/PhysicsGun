// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialEntity.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

// Sets default values
ASpecialEntity::ASpecialEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpecialEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpecialEntity::Setup_Implementation(const UPrimitiveComponent * comp, FVector location)
{
	UE_LOG(LogTemp, Warning, TEXT("somthing fucky"));
}

// Called every frame
void ASpecialEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

