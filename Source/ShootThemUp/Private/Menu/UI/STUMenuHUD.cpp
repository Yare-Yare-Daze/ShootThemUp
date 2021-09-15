// Shoot Them Up Game. All Rights Reserved

#include "Menu/UI/STUMenuHUD.h"
#include "STUBaseWidget.h"
#include "Blueprint/UserWidget.h"

void ASTUMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    
    if(MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<USTUBaseWidget>(GetWorld(), MenuWidgetClass);
        if(MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}
