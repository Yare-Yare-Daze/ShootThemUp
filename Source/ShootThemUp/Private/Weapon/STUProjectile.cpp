// Shoot Them Up Game. All Rights Reserved

#include "Weapon/STUProjectile.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STUWeaponFXComponent.h"


ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    SetLifeSpan(LifeSeconds);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if(!GetWorld()) return;

    MovementComponent->StopMovementImmediately();

    //make damage
    UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(),
        RadiusDamage, UDamageType::StaticClass(), {}, this, GetController(), DoFullDamage);

    //DrawDebugSphere(GetWorld(), GetActorLocation(), RadiusDamage, 24, FColor::Red);
    WeaponFXComponent->PlayImpactFX(Hit);
    Destroy();
}

AController* ASTUProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}


