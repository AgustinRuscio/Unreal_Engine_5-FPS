/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "Shoot/Interfaces/IWeaponSecondatyAction.h"
#include "UWeaponAimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOT_API UUWeaponAimComponent : public UActorComponent, public IIWeaponSecondatyAction
{
	GENERATED_BODY()

public:
	UUWeaponAimComponent();

	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//
	
	virtual void SetValues() override { };
	virtual void SetValues(FVector CameraLocation, FVector AimLocation, class UCameraComponent* Camera, class UCurveFloat* TimeLineCurveFloat);

	virtual void ActionStart() override;
	virtual void ActionEnd() override;

	//------------------------------------------------------------------//
	//							Public Variables						//
	//------------------------------------------------------------------//

private:
	//------------------------------------------------------------------//
	//							Private Methods							//
	//------------------------------------------------------------------//

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void MoveCameraTimeLineTick(float deltaTime);
	
	UFUNCTION()
	void MoveCameraTimeLineFinished();

	//------------------------------------------------------------------//
	//							Private Variables						//
	//------------------------------------------------------------------//

	FVector OriginalCameraLocation;
	FVector AimCameraLocation;

	class UCameraComponent* PlayerCamera;

	FTimeline MoveCameraTimeLine;
	UCurveFloat* CurveFloat;
};