#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Characters/CharHealing.h"
#include "PlayerHUD.generated.h"

UCLASS(Abstract)
class HEALINGPROJECT_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHealth(float CurrentHealth, float MaxHealth);

	void ReflexBarPerfect();

	void ResetReflexBar();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* ArmourBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* ReflexBar;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ReflexPerfectImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* FlasksIcon;

	float CurrentReflexPercent;


	FTimerHandle ReflexFillBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharHealing* Character;



};