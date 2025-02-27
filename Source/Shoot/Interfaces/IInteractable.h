/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"


UINTERFACE(MinimalAPI)
class UIInteractable : public UInterface
{
	GENERATED_BODY()
};


class SHOOT_API IIInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact() = 0;
	virtual void Interact(class AShootPlayer* PlayerInteractro) 
	{
		Interact();
	}

};