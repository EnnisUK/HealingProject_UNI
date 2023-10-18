// Fill out your copyright notice in the Description page of Project Settings.


#include "DmgBox.h"
#include "Kismet/GameplayStatics.h"





// Sets default values
ADmgBox::ADmgBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>("DmgHitBox");
	HitBox->InitBoxExtent(FVector(15, 15, 15));

}

// Called when the game starts or when spawned
void ADmgBox::BeginPlay()
{
	Super::BeginPlay();

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ADmgBox::OnBeginOverlap);
	HitBox->OnComponentEndOverlap.AddDynamic(this, &ADmgBox::OnEndOverlap);


	
}

void ADmgBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorld()->GetTimerManager().SetTimer(m_DmgTimerHandle, 0.1, true);
}

void ADmgBox::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetWorld()->GetTimerManager().ClearTimer(m_DmgTimerHandle);
}

void ADmgBox::DmgPlayer()
{
	
}

// Called every frame
void ADmgBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DeltaSeconds = DeltaTime;

}

