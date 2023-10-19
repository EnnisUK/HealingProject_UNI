
#include "BuffSelectMenu.h"
#include "Components/CanvasPanel.h"
#include "PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/Public/Components/Button.h"
#include "MyEnums.h"

void UBuffSelectedMenu::HideMenu()
{
	check(this);
	CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("HideMenu"));
}

void UBuffSelectedMenu::ShowMenu()
{
	check(this);
	CanvasPanel->SetVisibility(ESlateVisibility::Visible);
}
