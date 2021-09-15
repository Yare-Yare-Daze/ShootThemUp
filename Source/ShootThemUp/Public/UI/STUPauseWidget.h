// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "STUBaseWidget.h"
#include "STUPauseWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUPauseWidget : public USTUBaseWidget
{
	GENERATED_BODY()
public:
    

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnClearPause();
    
};
