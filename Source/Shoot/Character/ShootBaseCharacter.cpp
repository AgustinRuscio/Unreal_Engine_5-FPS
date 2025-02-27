/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "ShootBaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Shoot/Framework/ShootController.h"

//-----------------------------------------------------------------------------------------------
AShootBaseCharacter::AShootBaseCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;
}

//-----------------------------------------------------------------------------------------------
void AShootBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto controller = Cast<AShootController>(Controller);

	if (!controller) return;

	controller->OnMoveSidesDelegate.AddDynamic(this, &AShootBaseCharacter::InputMoveSides);
	controller->OnLookDelegate.AddDynamic(this, &AShootBaseCharacter::InputLook);

	controller->OnInteractDelegate.AddDynamic(this, &AShootBaseCharacter::InputInteract);

	controller->OnJumpDelegate.AddDynamic(this, &AShootBaseCharacter::InputJump);
}

//-----------------------------------------------------------------------------------------------
void AShootBaseCharacter::InputMoveSides(double value) { }

//-----------------------------------------------------------------------------------------------
void AShootBaseCharacter::InputLook(FVector2D value) { }

//-----------------------------------------------------------------------------------------------
void AShootBaseCharacter::InputInteract() { }

//-----------------------------------------------------------------------------------------------
void AShootBaseCharacter::InputJump() { }