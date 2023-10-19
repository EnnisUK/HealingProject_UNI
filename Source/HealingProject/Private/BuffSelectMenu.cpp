
#include "BuffSelectMenu.h"
#include "Components/CanvasPanel.h"
#include "PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/Public/Components/Button.h"
#include "MyEnums.h"

void UBuffSelectedMenu::NativeConstruct()
{
	Super::NativeConstruct();

	IncreasedHealButton->OnClicked.AddDynamic(this, &UBuffSelectedMenu::OnHealClicked);
}

void UBuffSelectedMenu::OnHealClicked()
{
	Character->ChosenBuff = ESelectedBuff::IncreasedHeal;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Heal Buff Selected"));
}
