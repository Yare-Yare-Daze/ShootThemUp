// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "STUBaseWidget.h"
#include "STUGameOverWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public USTUBaseWidget
{
	GENERATED_BODY()
public:


protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    virtual void NativeOnInitialized() override;
    
private:
    void OnMatchStateChanged(ESTUMatchState State);
    void UpdatePlayerStat();

    UFUNCTION()
    void OnResetLevel();
};
