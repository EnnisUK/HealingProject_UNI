// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/CharHealing.h"
#include "Components/BoxComponent.h"
#include "HealPotPickup.generated.h"

UCLASS()
class HEALINGPROJECT_API AHealPotPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealPotPickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_Mesh;


	UPROPERTY(EditAnywhere)
	UBoxComponent* m_HitBox;

	ACharHealing* m_Character;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
