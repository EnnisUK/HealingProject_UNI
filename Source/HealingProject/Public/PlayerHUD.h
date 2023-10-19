#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

UCLASS(Abstract)
class HEALINGPROJECT_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHealth(float CurrentHealth, float MaxHealth);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HealthBar;


};