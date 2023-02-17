// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetSimulatePhysics(true);	
	StaticMesh->SetCollisionObjectType(ECC_PhysicsBody);
	StaticMesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::Exploded);
	RootComponent = StaticMesh;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(StaticMesh);
	RadialForce->Radius = 700.f;
	RadialForce->ImpulseStrength = 2000.f;
	RadialForce->Falloff = RIF_Constant;
	RadialForce->bImpulseVelChange = true;
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	/*FScriptDelegate OnHitDel;
	OnHitDel.BindUFunction(this, "Exploded");
	StaticMesh->OnComponentHit.Add(OnHitDel);*/
}

void ASExplosiveBarrel::Exploded(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForce->FireImpulse();
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

