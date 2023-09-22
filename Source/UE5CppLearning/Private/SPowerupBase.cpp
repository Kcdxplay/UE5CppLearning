// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupBase.h"

// Sets default values
ASPowerupBase::ASPowerupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerUpMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("PowerUpMesh");
	RootComponent = PowerUpMeshComp;
}

void ASPowerupBase::Interact_Implementation(APawn* InstigatorPawn)
{
	if (ApplyPowerUp(InstigatorPawn))
	{
		PowerUpMeshComp->SetVisibility(false);
		SetActorEnableCollision(false);

		GetWorldTimerManager().SetTimer(RespawnTimeHandler, this, &ASPowerupBase::RespawnTimeElapsed, RespawnTime);
	}
}

// Called when the game starts or when spawned
void ASPowerupBase::BeginPlay()
{
	Super::BeginPlay();

}

bool ASPowerupBase::ApplyPowerUp(APawn* InstigatorPawn)
{
	return false;
}

void ASPowerupBase::RespawnTimeElapsed()
{
	PowerUpMeshComp->SetVisibility(true);
	SetActorEnableCollision(true);
}

// Called every frame
void ASPowerupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

