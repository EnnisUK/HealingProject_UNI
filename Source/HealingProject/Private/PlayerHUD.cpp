

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


	if (ReflexBar->Percent < 1.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ReflexFillBar, this, &UPlayerHUD::ReflexBarPerfect, 0.1, true);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ReflexFillBar);
		ReflexBar->SetPercent(0);
	}
	
}
