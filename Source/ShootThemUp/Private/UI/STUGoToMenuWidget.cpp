// Shoot Them Up Game. All Rights Reserved

#include "UI/STUGoToMenuWidget.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogGoToMenuWidget, All, All);

void USTUGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(BackToMenuButton)
    {
        BackToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnBackToMenu);
    }
}

void USTUGoToMenuWidget::OnBackToMenu()
{
    if(!GetWorld()) return;

    const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if(!STUGameInstance) return;

    if(STUGameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogGoToMenuWidget, Error, TEXT("Menu level name is None!"));
        
        return;
    }

    const FName MenuLevelName = STUGameInstance->GetMenuLevelName();
    UGameplayStatics::OpenLevel(this, MenuLevelName);
}

