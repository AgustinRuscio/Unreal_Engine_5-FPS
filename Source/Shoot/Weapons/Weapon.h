/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shoot/GameObjects/UsableObject.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class ESecondaryAction : uint8
{
	ESA_None, 
	ESA_Aim,
	ESA_ChangeShootBehavior
};

UCLASS()
class SHOOT_API AWeapon : public AUsableObject
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	//------------------------------------------------------------------//
	//							Public Components						//
	//------------------------------------------------------------------//

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* AimCameraLocation;

	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//

	virtual void PrimaryActionStart() override;
	virtual void PrimaryActionEnd() override;

	virtual void SecondaryActionStart() override;
	virtual void SecondaryActionEnd() override;

	//------------------------------------------------------------------//
	//							Public Variables						//
	//------------------------------------------------------------------//

private:

	//------------------------------------------------------------------//
	//							Private Methods							//
	//------------------------------------------------------------------//

	virtual void BeginPlay() override;

	void PrepareAimCofig();

	//------------------------------------------------------------------//
	//							Private Variables						//
	//------------------------------------------------------------------//

	bool bIsBot;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Settings")
	ESecondaryAction SecondaryActionType;

	class IIWeaponSecondatyAction* CurrentSecondaryAction;

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UCurveFloat* AimCurveFloat;
};