// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMagicProjectile.h"
#include "SMagicDashProjectile.generated.h"


class UParticleSystem;


/**
 * 
 */
UCLASS()
class UE5CPPLEARNING_API ASMagicDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	float FlyingTime = 0.2f;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ExitParticle;

	FTimerHandle TeleportTimeHandle;
	
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	void FlyingTimeElasped();
	void ParticleTimeElasped();

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
