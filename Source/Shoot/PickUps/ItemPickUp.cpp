/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "ItemPickUp.h"
#include "Shoot/Character/ShootPlayer.h"
#include "Components/SphereComponent.h"

//-----------------------------------------------------------------------------------------------
AItemPickUp::AItemPickUp()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	RootComponent = SphereCollider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SphereCollider);
}

//-----------------------------------------------------------------------------------------------
void AItemPickUp::Interact() { }

//-----------------------------------------------------------------------------------------------
void AItemPickUp::Interact(AShootPlayer* PlayerInteractro)
{
	PlayerInteractro->GetWeapon();
	Destroy();
}