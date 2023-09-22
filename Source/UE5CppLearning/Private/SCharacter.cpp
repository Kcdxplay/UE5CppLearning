// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject< USAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	AddMovementInput(ControlRot.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	FVector RightVec = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVec, value);
}

void ASCharacter::PrimaryAttack()
{
	CurrentProjectileIndex = 0;

	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FVector Start = CameraComp->GetComponentLocation();
	FVector Forward = CameraComp->GetForwardVector();

	FVector End = Start + (Forward * 5000);

	FHitResult HitDynamic;
	FHitResult HitStatic;

	bool bIsHitedDynamic = GetWorld()->LineTraceSingleByChannel(HitDynamic, Start, End, ECollisionChannel::ECC_WorldDynamic);
	bool bIsHitedStatic = GetWorld()->LineTraceSingleByChannel(HitStatic, Start, End, ECollisionChannel::ECC_WorldStatic);

	FVector AimLocation;

	if (bIsHitedDynamic && bIsHitedStatic)
	{
		AimLocation = HitDynamic.Distance < HitStatic.Distance ?
			HitDynamic.ImpactPoint :
			HitStatic.ImpactPoint;
	}
	else
	{
		if (bIsHitedDynamic)
		{
			AimLocation = HitDynamic.ImpactPoint;
		}
		else if (bIsHitedStatic)
		{
			AimLocation = HitStatic.ImpactPoint;
		}
		else
		{
			AimLocation = End;
		}
	}


	FRotator AimRotator = UKismetMathLibrary::FindLookAtRotation(HandLocation, AimLocation);
	FTransform SpawnTM = FTransform(AimRotator, HandLocation);


	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	AActor* ProjectileActor = GetWorld()->SpawnActor<AActor>(ProjectileClasses[CurrentProjectileIndex], SpawnTM, SpawnParams);

	if (ensure(AttackEffect))
	{
		UGameplayStatics::SpawnEmitterAttached(AttackEffect, GetMesh(), "Muzzle_01", HandLocation, AimRotator, EAttachLocation::KeepWorldPosition);
	}

	//ProjectileActor->SetOwner(this);
}

void ASCharacter::PrimaryBlackHole()
{
	CurrentProjectileIndex = FMath::Min(1, ProjectileClasses.Num() - 1);

	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ASCharacter::PrimaryTeleport()
{
	CurrentProjectileIndex = FMath::Min(2, ProjectileClasses.Num() - 1);

	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComop, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		//Get Damaged;
		this->FindComponentByClass<USkeletalMeshComponent>()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);

		if (NewHealth <= 0.f)
		{
			APlayerController* PC = Cast<APlayerController >(GetController());
			DisableInput(PC);
		}
	}
	else
	{
		//Get Healed;
	}

}



// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("BlackHoleProjectile", IE_Pressed, this, &ASCharacter::PrimaryBlackHole);
	PlayerInputComponent->BindAction("TeleportProjectile", IE_Pressed, this, &ASCharacter::PrimaryTeleport);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
}

