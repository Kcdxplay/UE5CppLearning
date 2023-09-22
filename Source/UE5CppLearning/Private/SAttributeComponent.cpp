// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}


bool USAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

bool USAttributeComponent::IsLowHealth() const
{
	return Health / HealthMax < 0.5f;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float HealthDelta)
{
	if (HealthDelta > 0.f && Health >= HealthMax)
	{
		return false;
	}

	Health += HealthDelta;
	Health = FMath::Clamp(Health, 0, HealthMax);

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, HealthDelta);

	return true;
}


USAttributeComponent* USAttributeComponent::GetAttributeComp(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* FromActor)
{
	if (!FromActor)
	{
		return false;
	}

	USAttributeComponent* AttributeComp = GetAttributeComp(FromActor);
	if (!AttributeComp)
	{
		return false;
	}

	return AttributeComp->IsAlive();
}

