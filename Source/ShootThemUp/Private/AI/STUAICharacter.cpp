// Shoot Them Up Game. All Rights Reserved


#include "AI/STUAICharacter.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTUAICharacter::StaticClass();
}
