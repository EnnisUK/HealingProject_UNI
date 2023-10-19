// Fill out your copyright notice in the Description page of Project Settings.


#include "DmgBox.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/CharHealing.h"






// Sets default values
ADmgBox::ADmgBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>("DmgHitBox");
	HitBox->InitBoxExtent(FVector(150, 150, 150));


	
}

// Called when the game starts or when spawned
void ADmgBox::BeginPlay()
{
	Super::BeginPlay();

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ADmgBox::OnBeginOverlap);
	HitBox->OnComponentEndOverlap.AddDynamic(this, &ADmgBox::OnEndOverlap);

	
	m_Character = Cast<ACharHealing>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ADmgBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(ACharacter::StaticClass()))
	{
		
		GetWorld()->GetTimerManager().SetTimer(m_DmgTimerHandle, this,&ADmgBox::DmgPlayer,0.1, true);
	}
	
}

void ADmgBox::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->IsChildOf(ACharacter::StaticClass()))
	{
		
		GetWorld()->GetTimerManager().ClearTimer(m_DmgTimerHandle);
	}
}

void ADmgBox::DmgPlayer()
{
	m_Character->m_Health -= DmgAmount * m_DeltaSeconds;
	m_Character->UpdateHealth();
}

// Called every frame
void ADmgBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DeltaSeconds = DeltaTime;

}

