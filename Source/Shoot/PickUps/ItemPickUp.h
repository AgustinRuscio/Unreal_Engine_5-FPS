/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shoot/Interfaces/IInteractable.h"
#include "ItemPickUp.generated.h"

UCLASS()
class SHOOT_API AItemPickUp : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	AItemPickUp();

	//------------------------------------------------------------------//
	//							Public Components						//
	//------------------------------------------------------------------//

	UPROPERTY(EditDefaultsOnly ,Category = Visuals, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollider;

	UPROPERTY(EditDefaultsOnly ,Category = Visuals, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;


	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//

	virtual void Interact() override;
	virtual void Interact(class AShootPlayer* PlayerInteractro) override;

private:
	//------------------------------------------------------------------//
	//							Private Methods							//
	//------------------------------------------------------------------//
	
	//------------------------------------------------------------------//
	//							Private Variables						//
	//------------------------------------------------------------------//

};
