

#include "PlayerHUD.h"
#include "Components/ProgressBar.h"


void UPlayerHUD::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

void UPlayerHUD::ReflexBarPerfect()
{
	ReflexBar->SetPercent(ReflexBar->Percent + 0.1);
	CurrentReflexPercent = ReflexBar->Percent;

	if (ReflexBar->Percent < 1.2f)
	{
		GetWorld()->GetTimerManager().SetTimer(ReflexFillBar, this, &UPlayerHUD::ReflexBarPerfect, 0.15, true);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ReflexFillBar);
		ReflexBar->SetPercent(0);
		CurrentReflexPercent = 0;
		Character->bIsHealing = false;

		
	}
	
}
