// Shoot Them Up Game. All Rights Reserved

#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

    WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshComponent");
    SetRootComponent(WeaponMeshComponent);
    
}

void ASTUBaseWeapon::StartFire()
{
    
}

void ASTUBaseWeapon::StopFire()
{
    
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

    check(WeaponMeshComponent);
    CurrentAmmo = DefaultAmmo;
}

void ASTUBaseWeapon::MakeShot()
{
    
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
    const ACharacter* Player = Cast<ACharacter>(GetOwner());
    if(!Player) return nullptr;

    return Player->GetController<APlayerController>();
    
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const APlayerController* Controller = GetPlayerController();
    if(!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
    
    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistant;
    return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if(!GetWorld()) return;
    
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ASTUBaseWeapon::DecreaseBullet()
{
    CurrentAmmo.Bullets--;
    LogAmmo();

    if(IsClipEmpty() && !IsAmmoEmpty())
    {
        ChangeClip();
    }
}

bool ASTUBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

void ASTUBaseWeapon::ChangeClip()
{
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    if(!CurrentAmmo.Infinite)
    {
        CurrentAmmo.Clips--;
    }
    UE_LOG(LogBaseWeapon, Display, TEXT("----- Changed Clip -----"));
}

void ASTUBaseWeapon::LogAmmo()
{
    FString StringAmmo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    StringAmmo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *StringAmmo);
}




