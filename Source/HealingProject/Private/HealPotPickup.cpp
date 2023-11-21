// Fill out your copyright notice in the Description page of Project Settings.


#include "HealPotPickup.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AHealPotPickup::AHealPotPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	m_HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	m_HitBox->SetupAttachment(m_Mesh);


}

// Called when the game starts or when spawned
void AHealPotPickup::BeginPlay()
{
	Super::BeginPlay();

	m_HitBox->OnComponentBeginOverlap.AddDynamic(this, &AHealPotPickup::OnSphereBeginOverlap);
	
}

void AHealPotPickup::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	m_Character = Cast<ACharHealing>(OtherActor);
	if (m_Character)
	{
		
		m_Character->m_HealingFlasks = 5;
		
	}
}

// Called every frame
void AHealPotPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

