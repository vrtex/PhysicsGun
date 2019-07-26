// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PhysicsGunProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "SpecialEntity.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

APhysicsGunProjectile::APhysicsGunProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->SetEnableGravity(false);
	CollisionComp->OnComponentHit.AddDynamic(this, &APhysicsGunProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->ProjectileGravityScale = 0;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void APhysicsGunProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ASpecialEntity * spawned = nullptr;
	if(ObjectToSpawn)
		spawned = GetWorld()->SpawnActor<ASpecialEntity>(ObjectToSpawn.Get(), Hit.ImpactPoint, UKismetMathLibrary::FindLookAtRotation(Hit.ImpactPoint, Hit.ImpactPoint + Hit.ImpactNormal));
	
	if(spawned)
		spawned->Setup(OtherComp, Hit.ImpactPoint);

	Destroy();
}