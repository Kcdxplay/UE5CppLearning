// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerupBase.generated.h"

UCLASS()
class UE5CPPLEARNING_API ASPowerupBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASPowerupBase();


	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:



	UPROPERTY(EditAnywhere, Category = "PowerUps")
	float RespawnTime = 10.f;


	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PowerUpMeshComp;

	FTimerHandle RespawnTimeHandler;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool ApplyPowerUp(APawn* InstigatorPawn);
	virtual void RespawnTimeElapsed();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
