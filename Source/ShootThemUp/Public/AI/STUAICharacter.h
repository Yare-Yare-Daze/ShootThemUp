// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

public:
    ASTUAICharacter(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    UBehaviorTree* BehaviorTree;

    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
    float HealthVisibilityDistance = 1000.0f;
    
    virtual void BeginPlay() override;
    virtual void OnHealthChanged(float Health, float HealthDelta) override;
    
    virtual void OnDeath() override;

private:
    void UpdateHealthWidgetVisibility();
};
