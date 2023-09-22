// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"


class UStaticMeshComponent;
class URadialForceComponent;


UCLASS()
class UE5CPPLEARNING_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	URadialForceComponent* RadialForce;


	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable)
	void Exploded(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
