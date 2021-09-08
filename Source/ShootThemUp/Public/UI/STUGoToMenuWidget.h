// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "STUGoToMenuWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* BackToMenuButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnBackToMenu();
    
};
