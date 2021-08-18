// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category="Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
    float RespawnTime = 5.0f;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    bool CouldBeTaken() const;

private:
    float RotationYaw = 0.0f;
    FTimerHandle RespawnTimerHandle;
    
    virtual bool GivePickupTo(APawn* PlayerPawn);
    
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
