// Shoot Them Up Game. All Rights Reserved

#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

    WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshComponent");
    SetRootComponent(WeaponMeshComponent);
    
}

void ASTUBaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


