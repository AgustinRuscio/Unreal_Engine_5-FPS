/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "Vehicle.h"
#include "Shoot/Character/ShootPlayer.h"
#include <Camera/CameraComponent.h>

//-----------------------------------------------------------------------------------------------
AVehicle::AVehicle() : bIsPossesed(false)
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
}

//-----------------------------------------------------------------------------------------------
void AVehicle::PossesVehicle()
{
	GetWorld()->GetFirstPlayerController()->Possess(this);
}

//-----------------------------------------------------------------------------------------------
void AVehicle::Interact()
{
	PossesVehicle();
}