/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */
#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "ShootController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveSidesDelegate, double, Direction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLookDelegate, FVector2D, Direction);

UCLASS()
class SHOOT_API AShootController : public APlayerController
{
	GENERATED_BODY()
	
public:

	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//

	//------------------------------------------------------------------//
	//							Public Variables						//
	//------------------------------------------------------------------//

	FOnInteractDelegate OnInteractDelegate;
	FOnJumpDelegate OnJumpDelegate;

	FOnMoveSidesDelegate OnMoveSidesDelegate;

	FOnLookDelegate OnLookDelegate;

private:

	//------------------------------------------------------------------//
	//							Private Methods							//
	//------------------------------------------------------------------//

	void BeginPlay();

	void BindInputActions();

	void InputActionMoveForward(const  FInputActionValue& Value);
	void InputActionMoveSides(const FInputActionValue& Value);

	void InputActionLook(const FInputActionValue& Value);

	void IputActionInteract();

	void IputActionJump();


	//------------------------------------------------------------------//
	//							Private Variables						//
	//------------------------------------------------------------------//

	/** MappingContext */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveForwardAction;

	/** Move Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveSidesAction;

	/** Sprint Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	/** Interact Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	/** Interact Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
};