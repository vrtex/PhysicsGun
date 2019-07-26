// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Runtime/CoreUObject/Public/UObject/Interface.h"
#include "Triggerable.generated.h"


UINTERFACE(BlueprintType)
class PHYSICSGUN_API UTriggerable : public UInterface
{
	GENERATED_BODY()
};


class PHYSICSGUN_API ITriggerable 
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interaction)
		void Trigger(bool on);
};
