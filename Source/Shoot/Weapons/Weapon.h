/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shoot/Interfaces/IUsableItem.h"
#include "Weapon.generated.h"

UCLASS()
class SHOOT_API AWeapon : public AActor, public IIUsableItem
{
	GENERATED_BODY()
	
public:	
	AWeapon();


	//------------------------------------------------------------------//
	//							Public Components						//
	//------------------------------------------------------------------//


	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//

	virtual void PrimaryAction() override;
	virtual void SecondaryAction() override;

	//------------------------------------------------------------------//
	//							Public Variables						//
	//------------------------------------------------------------------//

	float Damage = 10.f;
	float FireRate = 0.1f;

};