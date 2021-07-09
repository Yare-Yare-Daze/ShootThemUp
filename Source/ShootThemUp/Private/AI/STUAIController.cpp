// Shoot Them Up Game. All Rights Reserved


#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController()
{
    STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUPerceptionComponent");
    SetPerceptionComponent(*STUAIPerceptionComponent);
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto STUCharacter = Cast<ASTUAICharacter>(InPawn);
    if(STUCharacter)
    {
        RunBehaviorTree(STUCharacter->BehaviorTree);
    }
}

void ASTUAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const auto AimActor = STUAIPerceptionComponent->GetClosestEnemy();
    SetFocus(AimActor);
}
