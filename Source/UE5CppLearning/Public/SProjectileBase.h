// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"


class UParticleSystem;
class UParticleSystemComponent;
class USphereComponent;
class UProjectileMovementComponent;
class UAudioComponent;


UCLASS(ABSTRACT)
class UE5CPPLEARNING_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectileBase();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effects");
	UParticleSystem* ImpactVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Effects");
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShakeBase> CameraShake;
	UPROPERTY(EditAnywhere, Category = "Effects");
	float CameraShakeInnerRadius = 10.f;
	UPROPERTY(EditAnywhere, Category = "Effects");
	float CameraShakeOutterRadius = 200.f;
	UPROPERTY(EditAnywhere, Category = "Effects");
	float CameraShakeFallOff = 1.f;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UProjectileMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAudioComponent* AudioComp;


	virtual void PostInitializeComponents() override;

protected:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Explode();

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
