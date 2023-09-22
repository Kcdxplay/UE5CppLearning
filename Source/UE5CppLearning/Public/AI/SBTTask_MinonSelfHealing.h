// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTask_MinonSelfHealing.generated.h"


class UParticleSystem;


/**
 * 
 */
UCLASS()
class UE5CPPLEARNING_API USBTTask_MinonSelfHealing : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere,Category="Effects")
	UParticleSystem* HealingParticle;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
