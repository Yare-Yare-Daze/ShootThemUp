// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUPlayerController.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ASTUPlayerController();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USTURespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
    
private:
    void OnPauseGame();
    void OnMatchStateChanged(ESTUMatchState MatchState);
    
};
