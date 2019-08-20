// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleLineProjectile.h"
#include "GrappleLine.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GrappleLineTarget.h"

void AGrappleLineProjectile::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor *> otherProjectiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGrappleLineProjectile::StaticClass(), otherProjectiles);
	for(auto p : otherProjectiles)
	{
		if(p == this)
			continue;
		p->Destroy();
	}
}

void AGrappleLineProjectile::OnHitHandler(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AGrappleLineTarget * HitTarget = Cast<AGrappleLineTarget>(OtherActor);

	if(!HitTarget)
	{
		Destroy();
		return;
	}

	if(!ControlledLine)
	{
		UE_LOG(LogTemp, Error, TEXT("Grapple line projectile found target, but has no line"));
		Destroy();
		return;
	}

	ControlledLine->SetTarget(OtherActor);

	Wait();
	// Destroy();
}

void AGrappleLineProjectile::Setup_Implementation(UGrappleLine * LineComp)
{
	if(!LineComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Bogus line on setup"));
		return;
	}

	ControlledLine = LineComp;
	ControlledLine->OnComponentDeactivated.AddDynamic(this, &AGrappleLineProjectile::OnLineDeactivated);
}

void AGrappleLineProjectile::OnLineDeactivated(UActorComponent * Comp)
{
	Destroy();
}