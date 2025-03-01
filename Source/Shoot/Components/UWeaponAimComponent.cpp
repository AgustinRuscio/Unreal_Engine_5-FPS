/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "UWeaponAimComponent.h"
#include <Camera/CameraComponent.h>
#include <Components/ArrowComponent.h>
#include "GameFramework/Character.h"
#include "Math/UnrealMathUtility.h"


//-----------------------------------------------------------------------------------------------
UUWeaponAimComponent::UUWeaponAimComponent() : OriginalFOV(90.f), AimFOV(50.f)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::InitializeValues()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController) return;

	PlayerCamera = PlayerController->GetCharacter()->FindComponentByClass<UCameraComponent>();

	if (!PlayerCamera) return;

	OriginalFOV = PlayerCamera->FieldOfView;

	FOnTimelineFloat CameraTargetTick;
	CameraTargetTick.BindUFunction(this, FName("MoveNeedleTimeLineTick"));
	MoveNeedleTimeLine.AddInterpFloat(CurveFloat, CameraTargetTick);

	FOnTimelineEventStatic CameraTargettingFinished;
	CameraTargettingFinished.BindUFunction(this, FName("MoveNeedleTimeLineFinished"));
	MoveNeedleTimeLine.SetTimelineFinishedFunc(CameraTargettingFinished);
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::SetCameraFOV(float cameraFOV)
{
	OriginalFOV = cameraFOV;
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::ActionStart()
{
	MoveNeedleTimeLine.Play();
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::ActionEnd()
{
	MoveNeedleTimeLine.Reverse();
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveNeedleTimeLine.TickTimeline(DeltaTime);
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::MoveNeedleTimeLineTick(float deltaTime)
{
	auto NewFOV = FMath::Lerp(OriginalFOV, AimFOV, deltaTime);

	PlayerCamera->SetFieldOfView(NewFOV);
}

//-----------------------------------------------------------------------------------------------
void UUWeaponAimComponent::MoveNeedleTimeLineFinished() { }