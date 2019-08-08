// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Environment/Trigger.h"
#include "Environment/TriggerHolder.h"
#include "../../Plugins/Runtime/CableComponent/Source/CableComponent/Classes/CableComponent.h"

// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Start = CreateDefaultSubobject<USceneComponent>(TEXT("Start"));

	RootComponent = Start;

	End = CreateDefaultSubobject<USceneComponent>(TEXT("End"));
	End->SetupAttachment(GetRootComponent());

	BlockingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Blocking Point"));
	BlockingPoint->SetupAttachment(Start);
	BlockingPoint->SetWorldLocation(End->GetComponentLocation());

	Trigger = CreateDefaultSubobject<UTrigger>(TEXT("Trigger"));
	Trigger->OnTriggerOff.AddDynamic(this, &ALaser::TriggerOff);
	Trigger->OnTriggerOn.AddDynamic(this, &ALaser::TriggerOn);

	TriggerHolder = CreateDefaultSubobject<UTriggerHolder>(TEXT("Trigger Holder"));
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();

	// Connected = TraceLaser();
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(On)
		UpdateLaser(TraceLaser());

}

void ALaser::TriggerOn(AActor * User)
{
	TurnOn();
}

void ALaser::TriggerOff(AActor * User)
{
	TurnOff();
}

void ALaser::TurnOn()
{
	On = true;
}

void ALaser::TurnOff()
{
	On = false;
	BlockingPoint->SetWorldLocation(Start->GetComponentLocation());
	UpdateLaser(false);
}

void ALaser::UpdateLaser(bool newValue)
{
	if(Connected == newValue)
		return;

	if(newValue)
		Connect();
	else
		Block();
}

void ALaser::Connect()
{
	TriggerHolder->UseTriggers(true, this);
	Connected = true;
}

void ALaser::Block()
{
	TriggerHolder->UseTriggers(false, this);
	Connected = false;
}

bool ALaser::TraceLaser()
{
	FHitResult Hit;
	FCollisionObjectQueryParams objectParams;// (ECC_TO_BITFIELD(ECC_Pawn) | ECC_TO_BITFIELD(ECC_PhysicsBody));
	objectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	objectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams queryParams;
	queryParams.bTraceComplex = true;

	/*

	bool gotHit = GetWorld()->LineTraceSingleByChannel(Hit, Start->GetComponentLocation(), End->GetComponentLocation(), ECollisionChannel::ECC_Visibility);
	
	if(gotHit)
	{
		BlockingPoint->SetWorldLocation(gotHit ? Hit.ImpactPoint : End->GetComponentLocation());
		return false;
	}

	gotHit = GetWorld()->LineTraceSingleByChannel(Hit, Start->GetComponentLocation(), End->GetComponentLocation(), ECollisionChannel::ECC_Pawn);
	*/
	bool gotHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start->GetComponentLocation(), End->GetComponentLocation(), objectParams, queryParams);

	BlockingPoint->SetWorldLocation(gotHit ? Hit.ImpactPoint : End->GetComponentLocation());

	return !gotHit;

}