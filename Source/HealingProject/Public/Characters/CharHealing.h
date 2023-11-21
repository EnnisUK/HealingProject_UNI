// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnums.h"
#include "CharHealing.generated.h"




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

	// Variables

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int m_HealingFlasks;

	float m_DefaultHeal;

	float m_IncreasedHeal;

	UPROPERTY(BlueprintReadOnly)
	float ArmourAmount;

	UPROPERTY(BlueprintReadOnly)
	float ArmourMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float m_Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float m_MaxHealth = 100.f;

	bool bIsHealing;

	bool bReflexAttempted;

	bool bIsMenuOpen;

	FTimerHandle m_HealDelay;

	FTimerHandle m_SpeedBoostTimer;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ReflexSuccess;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ReflexFail;

	APlayerController* PC;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	//functions
	void ActivateHeal();


	void ReflexInput();
	
	void HealIsTrue();

	void ReflexBuffActivate();

	UFUNCTION(BlueprintCallable)
	void ClearBuffs();

	UFUNCTION(BlueprintCallable)
	void ShowMenu();




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Widget Class to spawn for the HUD*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerHUD> PlayerHUDClass;

	/* The widget instance that we are using as our HUD*/
	UPROPERTY()
	class UPlayerHUD* PlayerHUD;



	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBuffSelectedMenu> MenuHUDClass;

	/* The widget instance that we are using as our HUD*/
	UPROPERTY()
	class UBuffSelectedMenu* SelectBuffMenu;

	void UpdateHealth();

	UFUNCTION(BlueprintCallable)
	void DmgPlayer(float DmgAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESelectedBuff ChosenBuff = ESelectedBuff::IncreasedHeal;
	
};
