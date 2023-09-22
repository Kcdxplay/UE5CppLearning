// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicDashProjectile.h"
#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

void ASMagicDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TeleportTimeHandle, this, &ASMagicDashProjectile::FlyingTimeElasped,FlyingTime);
}

void ASMagicDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//SphereComp->OnComponentBeginOverlap.RemoveAll(this);
	//SphereComp->OnComponentHit.AddDynamic(this, &ASMagicDashProjectile::OnActorHit);
}

void ASMagicDashProjectile::FlyingTimeElasped()
{
	MoveComp->StopMovementImmediately();
	GetWorldTimerManager().ClearTimer(TeleportTimeHandle);

	//spawn teleport exit particle
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExitParticle,GetActorTransform());
	GetWorldTimerManager().SetTimer(TeleportTimeHandle, this, &ASMagicDashProjectile::ParticleTimeElasped, 0.2f);
}

void ASMagicDashProjectile::ParticleTimeElasped()
{
	GetInstigator()->SetActorLocation(GetActorLocation());

	Destroy();
}

void ASMagicDashProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FlyingTimeElasped();
}
