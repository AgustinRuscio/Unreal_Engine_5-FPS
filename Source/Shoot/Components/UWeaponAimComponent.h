/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "UWeaponAimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOT_API UUWeaponAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUWeaponAimComponent();

	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//
	void InitializeValues();

	void SetCameraFOV(float cameraFOV);

	void ActionStart();
	void ActionEnd();

	//------------------------------------------------------------------//
	//							Public Variables						//
	//------------------------------------------------------------------//

private:
	//------------------------------------------------------------------//
	//							Private Methods							//
	//------------------------------------------------------------------//
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void MoveNeedleTimeLineTick(float deltaTime);
	
	UFUNCTION()
	void MoveNeedleTimeLineFinished();

	//------------------------------------------------------------------//
	//							Private Variables						//
	//------------------------------------------------------------------//

	float OriginalFOV;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float AimFOV;

	FTimeline MoveNeedleTimeLine;

		UPROPERTY(EditAnywhere, Category = "Settings")
	UCurveFloat* CurveFloat;

	class UCameraComponent* PlayerCamera;
};