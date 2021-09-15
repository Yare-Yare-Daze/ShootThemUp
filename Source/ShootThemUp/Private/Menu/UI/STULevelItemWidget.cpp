// Shoot Them Up Game. All Rights Reserved

#include "Menu/UI/STULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTULevelItemWidget::SetLevelData(const FLevelData& Data)
{
    LevelData = Data;

    if(LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(Data.LevelName));
    }

    if(LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.LevelThumb);
    }
}

void USTULevelItemWidget::SetSelected(bool IsSelected)
{
    if(LevelImage)
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}

void USTULevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &USTULevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &USTULevelItemWidget::OnLevelItemUnhovered);
    }
}

void USTULevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USTULevelItemWidget::OnLevelItemHovered()
{
    if(FrameLevel)
    {
        FrameLevel->SetVisibility(ESlateVisibility::Visible);
    }   
}

void USTULevelItemWidget::OnLevelItemUnhovered()
{
    if(FrameLevel)
    {
        FrameLevel->SetVisibility(ESlateVisibility::Hidden);
    }
}
