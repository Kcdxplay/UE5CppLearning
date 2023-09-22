// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_MinonSelfHealing.h"
#include "AIModule/Classes/AIController.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type USBTTask_MinonSelfHealing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ensure(HealingParticle))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HealingParticle, AIPawn->GetActorLocation());
	}

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(AIPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	AttributeComp->ApplyHealthChange(AIPawn, 999999999.f);

	return EBTNodeResult::Succeeded;
}
