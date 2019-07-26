// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/CoreUObject/Public/UObject/Interface.h"
#include "IInteractable.generated.h"


UINTERFACE(BlueprintType)
class PHYSICSGUN_API UInteractable : public UInterface
{
	GENERATED_BODY()
};


class PHYSICSGUN_API IInteractable 
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interaction)
		bool Interact(AActor * interacting);
};
