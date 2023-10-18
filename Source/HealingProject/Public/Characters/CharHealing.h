// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharHealing.generated.h"

UENUM(BlueprintType)
enum class ESelectedBuff : uint8
{
	IncreasedHeal,
	Armour,
	SpeedIncrease,
	JumpHeight,

};


UCLASS()
class HEALINGPROJECT_API ACharHealing : public ACharacter
{
	GENERATED_BODY()



	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	ACharHealing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	//functions
	void ActivateHeal();



	// Variables

	int m_HealingFlasks;

	float m_DefaultHeal;

	float m_IncreasedHeal;

	float m_Health;

	float m_MaxHealth = 100.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
