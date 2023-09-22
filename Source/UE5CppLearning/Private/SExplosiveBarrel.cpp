// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetSimulatePhysics(true);	
	StaticMesh->SetCollisionObjectType(ECC_PhysicsBody);
	RootComponent = StaticMesh;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(StaticMesh);
	RadialForce->Radius = 700.f;
	RadialForce->ImpulseStrength = 2000.f;
	RadialForce->Falloff = RIF_Constant;
	RadialForce->bImpulseVelChange = true;
}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StaticMesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::Exploded);
}

void ASExplosiveBarrel::Exploded(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForce->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("Barrel has Exploded"));

	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game tiem: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);


	FString CombindString = FString::Printf(TEXT("Hit at Location %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombindString, nullptr, FColor::Green, 2.f, true, 2.f);
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

