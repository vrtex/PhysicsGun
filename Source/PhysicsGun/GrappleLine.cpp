// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleLine.h"
#include "PhysicsGunCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UGrappleLine::UGrappleLine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bAutoActivate = false;
	PrimaryComponentTick.bCanEverTick = true;

	OnComponentActivated.AddDynamic(this, &UGrappleLine::OnActivated);
	OnComponentDeactivated.AddDynamic(this, &UGrappleLine::OnDeactivated);
	// ...
}


// Called when the game starts
void UGrappleLine::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);

	ControlledCharacter = Cast<APhysicsGunCharacter>(GetOwner());
	if(!ControlledCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Grapple line no attached"));
	}
}

void UGrappleLine::OnActivated(UActorComponent * Component, bool bReset)
{
	ControlledCharacter->SetControllsEnabled(false);
	SetComponentTickEnabled(true);
	UE_LOG(LogTemp, Warning, TEXT("Active"));
	ControlledCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UGrappleLine::OnDeactivated(UActorComponent * Component)
{
	ControlledCharacter->SetControllsEnabled(true);
	SetComponentTickEnabled(false);
	UE_LOG(LogTemp, Warning, TEXT("Not Active"));
	ControlledCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
}

void UGrappleLine::SetTarget(FVector NewTarget)
{
	Activate();
	CurrentTarget = NewTarget;
}

// Called every frame
void UGrappleLine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector currentLocation = ControlledCharacter->GetActorLocation();
	FVector direction = (CurrentTarget - currentLocation);

	if(direction.Size() < DistanceTolerance)
	{
		Deactivate();
		return;
	}
	float speedMultipler = FMath::Clamp(direction.Size() / SmoothingDistance, 0.5f, 1.5f);


	direction.Normalize();

	ControlledCharacter->AddMovementInput(direction, FMath::Lerp(0.f,  PullingSpeed, speedMultipler) * DeltaTime);

}

