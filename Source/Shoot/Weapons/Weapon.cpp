/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "Weapon.h"
#include "Shoot/Components/UWeaponAimComponent.h"
#include "Components/TimelineComponent.h"
#include "Shoot/Components/UShootComponent.h"
#include <Shoot/Character/ShootPlayer.h>

//-----------------------------------------------------------------------------------------------
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	ShootComponent = CreateDefaultSubobject<UUShootComponent>(TEXT("ShootComponent"));
	
	AimComponent = CreateDefaultSubobject<UUWeaponAimComponent>("AimComponent");
	
	
}

//-----------------------------------------------------------------------------------------------
void AWeapon::PrimaryActionStart()
{
	ShootComponent->StartShoot();
}

//-----------------------------------------------------------------------------------------------
void AWeapon::PrimaryActionEnd()
{
	ShootComponent->EndShoot();
}

//-----------------------------------------------------------------------------------------------
void AWeapon::SecondaryActionStart()
{
	switch (SecondaryActionType)
	{
	case ESecondaryAction::ESA_Aim:
		AimComponent->ActionStart();
		break;

	case ESecondaryAction::ESA_ChangeShootBehavior:
		ShootComponent->SwitchShootBehavior();
		break;

	case ESecondaryAction::ESA_None:
	default:
		break;
	}
;
}

//-----------------------------------------------------------------------------------------------
void AWeapon::SecondaryActionEnd()
{
	switch (SecondaryActionType)
	{
	case ESecondaryAction::ESA_Aim:
		AimComponent->ActionEnd();
		break;

	case ESecondaryAction::ESA_None:
	case ESecondaryAction::ESA_ChangeShootBehavior:
	default:
		break;
	}
}

//-----------------------------------------------------------------------------------------------
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	ShootComponent->SetOwner(GetOwner());
	AimComponent->InitializeValues();
}

void AWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//-----------------------------------------------------------------------------------------------
void AWeapon::InitializeComponents()
{
}