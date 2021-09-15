// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUGameModeBase.h"
#include "STUPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetTotalRoundNum() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetRoundSecondsRemaining() const;

private:
    ASTUGameModeBase* GetSTUGameMode() const;
    ASTUPlayerState* GetSTUPlayerState() const;
};
