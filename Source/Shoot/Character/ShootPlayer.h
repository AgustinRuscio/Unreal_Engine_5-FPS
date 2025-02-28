/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootBaseCharacter.h"
#include "ShootPlayer.generated.h"

UCLASS()
class SHOOT_API AShootPlayer : public AShootBaseCharacter
{
	GENERATED_BODY()

public:
	AShootPlayer();

	//------------------------------------------------------------------//
	//							Public Components						//
	//------------------------------------------------------------------//
	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh;

	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//
	void GetUsableItem(TSubclassOf<class AUsableObject> UsableItem);

	//------------------------------------------------------------------//
	//							Public Variables						//
	//------------------------------------------------------------------//

protected:
	//------------------------------------------------------------------//
	//						Protected Methods							//
	//------------------------------------------------------------------//
	
	// Input Methods
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void InputMoveSides(double value) override;

	virtual void InputLook(FVector2D value) override;

	virtual void InputInteract() override;

	virtual void InputJump() override;

	UFUNCTION()
	void IputActionSprint(const FInputActionValue& Value);

	UFUNCTION()
	void IputActionCrouch(const FInputActionValue& Value);

	UFUNCTION()
	void IputActionPrimaryStart(const FInputActionValue& Value);
	
	UFUNCTION()
	void IputActionPrimaryEnd(const FInputActionValue& Value);
	
	UFUNCTION()
	void IputActionSecondaryStart(const FInputActionValue& Value);

	UFUNCTION()
	void IputActionSecondaryEnd(const FInputActionValue& Value);

	//------------------------------------------------------------------//
	//						Protected Variables							//
	//------------------------------------------------------------------//

	
	/** MappingContext */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Sprint Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	/** Sprint Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

	/** Actions Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* PrimaryAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SecondaryAction;

private:
	//------------------------------------------------------------------//
	//							Private Methods							//
	//------------------------------------------------------------------//

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void DrawTraceLine();

	//------------------------------------------------------------------//
	//							Private Variables						//
	//------------------------------------------------------------------//

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float TraceDistance = 1000.f;

	class IIInteractable* CurretnInteractable = nullptr;

	class AUsableObject* CurrentUsable;

};