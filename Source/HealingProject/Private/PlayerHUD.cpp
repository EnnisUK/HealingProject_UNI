

#include "PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"



void UPlayerHUD::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

void UPlayerHUD::ReflexBarPerfect()
{
	ReflexBar->SetPercent(ReflexBar->Percent + 0.02 / 1);
	CurrentReflexPercent = ReflexBar->Percent;

	if (!ReflexBar->IsVisible() && !ReflexPerfectImage->IsVisible())
	{
		ReflexBar->SetVisibility(ESlateVisibility::Visible);
		ReflexPerfectImage->SetVisibility(ESlateVisibility::Visible);
	}
	
	


	if (ReflexBar->Percent < 1)
	{
		GetWorld()->GetTimerManager().SetTimer(ReflexFillBar, this, &UPlayerHUD::ReflexBarPerfect, 0.05, true);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ReflexFillBar);
		ResetReflexBar();
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("RESET HAS BEEN CALLED"));
		
	}
	
}

void UPlayerHUD::ResetReflexBar()
{
	ReflexBar->SetPercent(0);
	ReflexBar->SetVisibility(ESlateVisibility::Hidden);
	ReflexPerfectImage->SetVisibility(ESlateVisibility::Hidden);
	CurrentReflexPercent = 0;
	Character->bIsHealing = false;
	Character->bReflexAttempted = false;

	UGameplayStatics::PlaySound2D(GetWorld(), Character->ReflexFail, 0.3);


}
