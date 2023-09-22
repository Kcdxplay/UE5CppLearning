// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthHealer.h"
#include "SAttributeComponent.h"

bool ASHealthHealer::ApplyPowerUp(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (AttributeComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("The User of %s HealthHealer is %s"), *GetNameSafe(this), *GetNameSafe(InstigatorPawn));

		return AttributeComp->ApplyHealthChange(this, HealthHealAmount);
	}

	return false;
}
