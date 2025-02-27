/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootBaseCharacter.generated.h"

UCLASS()
class SHOOT_API AShootBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShootBaseCharacter();
	
	//------------------------------------------------------------------//
	//							Public Components						//
	//------------------------------------------------------------------//
	
	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//

	//------------------------------------------------------------------//
	//							Public Variables						//
	//------------------------------------------------------------------//


protected:
	//------------------------------------------------------------------//
	//						Protected Methods							//
	//------------------------------------------------------------------//
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void InputMoveSides(double value);

	UFUNCTION()
	virtual void InputLook(FVector2D value);

	UFUNCTION()
	virtual void InputInteract();

	UFUNCTION()
	virtual void InputJump();

	//------------------------------------------------------------------//
	//						Protected Variables							//
	//------------------------------------------------------------------//

private:
	//------------------------------------------------------------------//
	//							Private Methods							//
	//------------------------------------------------------------------//

	//------------------------------------------------------------------//
	//							Private Variables						//
	//------------------------------------------------------------------//
};