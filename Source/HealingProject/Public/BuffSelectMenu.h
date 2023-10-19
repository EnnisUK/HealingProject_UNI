#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Characters/CharHealing.h"
#include "BuffSelectMenu.generated.h"


UCLASS(Abstract)
class HEALINGPROJECT_API UBuffSelectedMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void HideMenu();

	void ShowMenu();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ArmorButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SpeedBoostButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* JumpHeightButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* IncreasedHealButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharHealing* Character;

};