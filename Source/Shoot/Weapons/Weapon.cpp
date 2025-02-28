/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "Weapon.h"
#include <Camera/CameraComponent.h>
#include <Components/ArrowComponent.h>
#include "Shoot/Components/UWeaponAimComponent.h"
#include <Shoot/Character/ShootPlayer.h>

//-----------------------------------------------------------------------------------------------
AWeapon::AWeapon() : bIsBot(false), SecondaryActionType(ESecondaryAction::ESA_None), CurrentSecondaryAction(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	AimCameraLocation = CreateDefaultSubobject<UArrowComponent>("AimLocation");
	AimCameraLocation->SetupAttachment(ObjectMesh);
}

//-----------------------------------------------------------------------------------------------
void AWeapon::PrimaryActionStart()
{
}

//-----------------------------------------------------------------------------------------------
void AWeapon::PrimaryActionEnd()
{
}

//-----------------------------------------------------------------------------------------------
void AWeapon::SecondaryActionStart()
{
	if(CurrentSecondaryAction)
		CurrentSecondaryAction->ActionStart();
}

//-----------------------------------------------------------------------------------------------
void AWeapon::SecondaryActionEnd()
{
	if (CurrentSecondaryAction)
		CurrentSecondaryAction->ActionEnd();
}

//-----------------------------------------------------------------------------------------------
void AWeapon::BeginPlay()
{
	if (!bIsBot)
	{
		switch (SecondaryActionType)
		{
		case ESecondaryAction::ESA_Aim:
			PrepareAimCofig();
			break;

		case ESecondaryAction::ESA_ChangeShootBehavior:
			break;

		case ESecondaryAction::ESA_None:
		default:
			CurrentSecondaryAction = nullptr;
			break;
		}
	}
}

void AWeapon::PrepareAimCofig()
{
	auto AimComp = NewObject<UUWeaponAimComponent>(this);
	AimComp->RegisterComponent();

	CurrentSecondaryAction = AimComp;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController) return;
	
	APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;

	if (!CameraManager) return;

	CurrentSecondaryAction->SetValues(CameraManager->GetCameraLocation(), AimCameraLocation->GetComponentLocation(), PlayerController->GetCharacter()->GetComponentByClass<UCameraComponent>(), AimCurveFloat);
}