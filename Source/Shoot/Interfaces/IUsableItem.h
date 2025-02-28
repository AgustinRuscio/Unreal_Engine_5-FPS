/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IUsableItem.generated.h"

UINTERFACE(MinimalAPI)
class UIUsableItem : public UInterface
{
	GENERATED_BODY()
};


class SHOOT_API IIUsableItem
{
	GENERATED_BODY()

public:

	virtual void PrimaryActionStart() = 0;
	virtual void PrimaryActionEnd() = 0;

	virtual void SecondaryActionStart() = 0;
	virtual void SecondaryActionEnd() = 0;
};