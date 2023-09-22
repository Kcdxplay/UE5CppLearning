// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;
class USInteractionComponent;
class USAttributeComponent;


UCLASS()
class UE5CPPLEARNING_API ASCharacter : public ACharacter
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TArray< TSubclassOf<AActor>> ProjectileClasses;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Attack");
	UParticleSystem* AttackEffect;

	FTimerHandle TimerHandle_PrimaryAttack;

	int CurrentProjectileIndex = 0;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	virtual void PostInitializeComponents() override;


	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components");
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components")
	USAttributeComponent* AttributeComp;	


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);

	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void PrimaryBlackHole();
	void PrimaryTeleport();
	void PrimaryInteract();


	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComop,float NewHealth, float Delta);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
