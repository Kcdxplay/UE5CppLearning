// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"
#include "SAttributeComponent.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/AIController.h"

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OwnerComp.GetAIOwner()->GetPawn()->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (ensure(BlackboardComp) && ensure(AttributeComp))
	{
		BlackboardComp->SetValueAsBool(LowHealthConditionKey.SelectedKeyName, AttributeComp->IsLowHealth());
	}
}
