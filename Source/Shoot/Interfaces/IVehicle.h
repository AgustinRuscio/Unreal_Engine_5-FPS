/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IVehicle.generated.h"

UINTERFACE(MinimalAPI)
class UIVehicle : public UInterface
{
	GENERATED_BODY()
};


class SHOOT_API IIVehicle
{
	GENERATED_BODY()

public:

	virtual void PossesVehicle() = 0;
};
