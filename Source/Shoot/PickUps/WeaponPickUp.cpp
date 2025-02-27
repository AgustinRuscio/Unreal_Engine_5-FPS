/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "WeaponPickUp.h"
#include "Shoot/Character/ShootPlayer.h"
#include "Components/SphereComponent.h"

//-----------------------------------------------------------------------------------------------
AWeaponPickUp::AWeaponPickUp()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	RootComponent = SphereCollider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SphereCollider);
}

//-----------------------------------------------------------------------------------------------
void AWeaponPickUp::Interact() { }

//-----------------------------------------------------------------------------------------------
void AWeaponPickUp::Interact(AShootPlayer* PlayerInteractro)
{
	PlayerInteractro->GetWeapon();
	Destroy();
}