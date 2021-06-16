// Shoot Them Up Game. All Rights Reserved

#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USTUWeaponComponent::StartFire()
{
    if(!CurrentWeapon) return;
    CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
    if(!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon()
{
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}


void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    CurrentWeaponIndex = 0;
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for(auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);   
}

void USTUWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!Character || !GetWorld()) return;

    for(auto WeaponClass : WeaponClasses)
    {
        auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
        if(!Weapon) continue;

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachToWeaponSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USTUWeaponComponent::AttachToWeaponSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName SocketName)
{
    if(!Weapon || !SceneComponent) return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false); 
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!Character) return;

    if(CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachToWeaponSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }
    
    CurrentWeapon = Weapons[WeaponIndex];
    AttachToWeaponSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
}


