/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shoot/Interfaces/IUsableItem.h"
#include "UsableObject.generated.h"

UCLASS()
class SHOOT_API AUsableObject : public AActor, public IIUsableItem
{
	GENERATED_BODY()
	
public:	
	AUsableObject();

	//------------------------------------------------------------------//
	//							Public Components						//
	//------------------------------------------------------------------//

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ObjectMesh;

	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//

	class AShootBaseCharacter* GetObjectOwner() const;

	virtual void PrimaryActionStart() override {};
	virtual void PrimaryActionEnd() override {};

	virtual void SecondaryActionStart() override {};
	virtual void SecondaryActionEnd() override {};

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

	class AShootBaseCharacter* ObjectOwner;
};