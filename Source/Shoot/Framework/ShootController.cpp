/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "ShootController.h"

//-----------------------------------------------------------------------------------------------
void AShootController::BeginPlay()
{
	BindInputActions();
}

//-----------------------------------------------------------------------------------------------
void AShootController::BindInputActions()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AShootController::InputActionMoveForward);

		EnhancedInputComponent->BindAction(MoveSidesAction, ETriggerEvent::Triggered, this, &AShootController::InputActionMoveSides);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShootController::InputActionLook);

		// Interact 
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AShootController::IputActionInteract);

		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AShootController::IputActionJump);
	}
}

//-----------------------------------------------------------------------------------------------
void AShootController::InputActionMoveForward(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), MovementVector.Y);
}

//-----------------------------------------------------------------------------------------------
void AShootController::InputActionMoveSides(const FInputActionValue& Value)
{
	OnMoveSidesDelegate.Broadcast(Value.Get<FVector2D>().X);
}

//-----------------------------------------------------------------------------------------------
void AShootController::InputActionLook(const FInputActionValue& Value)
{
	auto vector = Value.Get<FVector2D>();
	OnLookDelegate.Broadcast(vector);
}

//-----------------------------------------------------------------------------------------------
void AShootController::IputActionInteract()
{
	OnInteractDelegate.Broadcast();
}

//-----------------------------------------------------------------------------------------------
void AShootController::IputActionJump()
{
	OnJumpDelegate.Broadcast();
}