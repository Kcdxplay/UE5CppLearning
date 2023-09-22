// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupBase.h"
#include "SHealthHealer.generated.h"


class APawn;


UCLASS()
class UE5CPPLEARNING_API ASHealthHealer : public ASPowerupBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere,Category="PowerUps")
	float HealthHealAmount = 10.f;


protected:
	virtual bool ApplyPowerUp(APawn* InstigatorPawn) override;
};
