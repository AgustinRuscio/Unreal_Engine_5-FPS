/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWeaponSecondatyAction.generated.h"


UINTERFACE(MinimalAPI)
class UIWeaponSecondatyAction : public UInterface
{
	GENERATED_BODY()
};


class SHOOT_API IIWeaponSecondatyAction
{
	GENERATED_BODY()

public:
	virtual void SetValues() = 0;

	virtual void SetValues(FVector CameraLocation, FVector AimLocation, class UCameraComponent* Camera, class UCurveFloat* TimeLineCurveFloat) 
	{
		SetValues();
	}

	virtual void SetValues(class AWeapon* Weapon)
	{
		SetValues();
	};

	virtual void ActionStart() = 0;
	virtual void ActionEnd() = 0;
};