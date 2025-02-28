/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "UWeaponAimComponent.h"
#include <Camera/CameraComponent.h>
#include "Math/UnrealMathUtility.h"


//-----------------------------------------------------------------------------------------------
UUWeaponAimComponent::UUWeaponAimComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::SetValues(FVector CameraLocation, FVector AimLocation, UCameraComponent* Camera, UCurveFloat* TimeLineCurveFloat)
{
	OriginalCameraLocation = CameraLocation;
	AimCameraLocation = AimLocation;
	PlayerCamera = Camera;
	CurveFloat = TimeLineCurveFloat;
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::ActionStart()
{
	if (MoveCameraTimeLine.IsPlaying())
	{
		MoveCameraTimeLine.Stop();
	}

	MoveCameraTimeLine.Play();
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::ActionEnd()
{
	if (MoveCameraTimeLine.IsPlaying())
	{
		MoveCameraTimeLine.Stop();
	}

	MoveCameraTimeLine.Reverse();
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("MoveCameraTimeLineTick"));
	MoveCameraTimeLine.AddInterpFloat(CurveFloat, CameraTargetTick);

	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("MoveCameraTimeLineFinished"));
	MoveCameraTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveCameraTimeLine.TickTimeline(DeltaTime);
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::MoveCameraTimeLineTick(float deltaTime)
{
	auto NewLocation = FMath::Lerp(OriginalCameraLocation, AimCameraLocation, deltaTime);

	PlayerCamera->SetWorldLocation(NewLocation);
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::MoveCameraTimeLineFinished() { }