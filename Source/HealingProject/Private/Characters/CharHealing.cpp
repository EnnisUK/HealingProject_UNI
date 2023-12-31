// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharHealing.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "BuffSelectMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"




// Sets default values
ACharHealing::ACharHealing()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 800.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->GravityScale = 1.3;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Class Variable Defaults

	m_HealingFlasks = 5;
	m_DefaultHeal = 30;
	m_IncreasedHeal = 15;
	m_Health = m_MaxHealth;
	bIsHealing = false;
	ArmourMax = 100.f;

	// Create Widget
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;

	SelectBuffMenu = nullptr;
	MenuHUDClass = nullptr;
	
}

// Called when the game starts or when spawned
void ACharHealing::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));


	if (IsLocallyControlled() && PlayerHUDClass)
	{
		
		PlayerHUD = CreateWidget<UPlayerHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0), PlayerHUDClass);
		check(PlayerHUD);
		PlayerHUD->AddToPlayerScreen();
		PlayerHUD->SetHealth(m_Health, m_MaxHealth);
		
	}

	if (MenuHUDClass)
	{
		SelectBuffMenu = CreateWidget<UBuffSelectedMenu>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MenuHUDClass);
		check(SelectBuffMenu);
		SelectBuffMenu->HideMenu();
		SelectBuffMenu->AddToPlayerScreen();
	}
	
}

void ACharHealing::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACharHealing::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ACharHealing::ActivateHeal()
{
	FString HealString = FString::SanitizeFloat(m_Health);
	if (m_HealingFlasks > 0 && m_Health < 100 && bIsHealing == false)
	{
		GetWorld()->GetTimerManager().SetTimer(m_HealDelay, this, &ACharHealing::HealIsTrue, 0.15, false);
		m_Health += m_DefaultHeal;
		m_Health = FMath::Clamp(m_Health, 0, m_MaxHealth);
		
		UpdateHealth();

		m_HealingFlasks -= 1;

		PlayerHUD->ReflexBarPerfect();
	}
}

void ACharHealing::ReflexInput()
{
	if (bIsHealing == true && bReflexAttempted == false)
	{
	
		if (UKismetMathLibrary::InRange_FloatFloat(PlayerHUD->CurrentReflexPercent, 0.3, 0.4, true, true))
		{
			if (ReflexSuccess)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), ReflexSuccess, 0.3);
			}
			GetWorld()->GetTimerManager().ClearTimer(PlayerHUD->ReflexFillBar);
			PlayerHUD->ResetReflexBar();
			ReflexBuffActivate();
		}
		else
		{
			if (ReflexFail)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), ReflexFail, 0.3);
			}
			bReflexAttempted = true;
			GetWorld()->GetTimerManager().ClearTimer(PlayerHUD->ReflexFillBar);
			PlayerHUD->ResetReflexBar();
			
		}
	}

}

void ACharHealing::UpdateHealth()
{
	PlayerHUD->SetHealth(m_Health, m_MaxHealth);

}

void ACharHealing::HealIsTrue()
{
	bIsHealing = true;
}

// Called every frame
void ACharHealing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ACharHealing::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ACharHealing::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ACharHealing::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);



	//Custom Actions
	PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &ACharHealing::ActivateHeal);
	PlayerInputComponent->BindAction("Reflex", IE_Pressed, this, &ACharHealing::ReflexInput);
	PlayerInputComponent->BindAction("Menu", IE_Pressed, this, &ACharHealing::ShowMenu);

}

void ACharHealing::ShowMenu()
{
	if (bIsMenuOpen)
	{
		SelectBuffMenu->HideMenu();
		check(PC);
		PC->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
		bIsMenuOpen = false;
	}
	else
	{
		SelectBuffMenu->ShowMenu();
		PC->bShowMouseCursor = true;
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC, SelectBuffMenu);
		bIsMenuOpen = true;
	
	}
}


void ACharHealing::DmgPlayer(float DmgAmount)
{
	if (ArmourAmount > 0)
	{
		ArmourAmount -= DmgAmount;
		ArmourAmount = FMath::Clamp(ArmourAmount, 0, ArmourMax);

	}
	else
	{
		m_Health -= DmgAmount;
		m_Health = FMath::Clamp(m_Health, 0, m_MaxHealth);
	}

	if (m_Health == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Dead"));
	}

}

void ACharHealing::ReflexBuffActivate()
{
	switch (ChosenBuff)
	{
	case ESelectedBuff::IncreasedHeal:
		m_Health += m_IncreasedHeal;
		m_Health = FMath::Clamp(m_Health, 0, m_MaxHealth);
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("EXTRA HEAL"));
		UpdateHealth();
		break;
	case ESelectedBuff::Armour:
		ArmourAmount += 40;
		ArmourAmount = FMath::Clamp(ArmourAmount, 0, ArmourMax);

		break;
	case ESelectedBuff::SpeedIncrease:
		
		GetWorldTimerManager().SetTimer(m_SpeedBoostTimer, this, &ACharHealing::ClearBuffs, 4.0f, false);
		GetCharacterMovement()->MaxWalkSpeed = 1500;

		

		break;
	case ESelectedBuff::JumpHeight:
		GetCharacterMovement()->JumpZVelocity = 800;
		break;
	default:
		break;
	} 
}

void ACharHealing::ClearBuffs()
{
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 800.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->GravityScale = 1.3;
	ArmourAmount = 0;

}

