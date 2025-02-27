/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "Shoot/Interfaces/IVehicle.h"
#include "Shoot/Interfaces/IInteractable.h"
#include "GameFramework/Character.h"
#include "Vehicle.generated.h"

UCLASS(Abstract)
class SHOOT_API AVehicle : public ACharacter, public IIVehicle, public IIInteractable
{
	GENERATED_BODY()

public:
	AVehicle();
	
	//------------------------------------------------------------------//
	//							Public Component						//
	//------------------------------------------------------------------//
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//

	virtual void PossesVehicle() override;

	virtual void Interact() override;

	//------------------------------------------------------------------//
	//							Public Variables						//
	//------------------------------------------------------------------//



private:

	//------------------------------------------------------------------//
	//							Private Methods							//
	//------------------------------------------------------------------//

	//------------------------------------------------------------------//
	//							Private Variables						//
	//------------------------------------------------------------------//
	
	bool bIsPossesed = false;
};