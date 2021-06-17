// Shoot Them Up Game. All Rights Reserved

#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STUEquipFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USTUWeaponComponent::StartFire()
{
    if(!CanFire()) return;
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
    InitAnimations();
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
    EquipAnimInProgress = true;
    AttachToWeaponSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!Character) return;

    Character->PlayAnimMontage(Animation);
}

void USTUWeaponComponent::InitAnimations()
{
    if(!EquipAnimMontage) return;
    const auto NotifyEvents = EquipAnimMontage->Notifies;

    for(auto NotifyEvent : NotifyEvents)
    {
        auto EquipFinishedNotify = Cast<USTUEquipFinishedAnimNotify>(NotifyEvent.Notify);
        if(EquipFinishedNotify)
        {
            EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
        }
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!Character || Character->GetMesh() != MeshComponent) return;

    EquipAnimInProgress = false;
    
}

bool USTUWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress;
}


