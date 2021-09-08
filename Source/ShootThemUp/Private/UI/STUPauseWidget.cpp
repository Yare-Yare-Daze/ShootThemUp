// Shoot Them Up Game. All Rights Reserved


#include "UI/STUPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPauseWidget, All, All);

void USTUPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if(ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
    }
}

void USTUPauseWidget::OnClearPause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}

