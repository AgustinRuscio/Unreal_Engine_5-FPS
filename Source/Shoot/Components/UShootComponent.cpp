/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "UShootComponent.h"
#include "Math/UnrealMathUtility.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

namespace
{
    float TimeShootDiff = 0.;
    float SpreadAngle = 0.f;
}

//-----------------------------------------------------------------------------------------------
UUShootComponent::UUShootComponent() : bIsAutomatic(false), NumberOfBullets(0), ShootDistance(1000.f), FireRate(0.2f), SpreadAngleMin(0.f), SpreadAngleMax(5.f), SpreadPreShootIncrease(1.f), ShootRadius(2.f), DamagePerBullet(10.f), LastShootTime(0.f), OwnerPlayer(nullptr)
{
    PrimaryComponentTick.bCanEverTick = true;

    SpreadAngle = SpreadAngleMin;
}

//-----------------------------------------------------------------------------------------------
void UUShootComponent::SetOwner(AActor* WeaponOwner)
{
    OwnerPlayer = WeaponOwner;
}

#pragma region ACTION METHODS
//-----------------------------------------------------------------------------------------------
void UUShootComponent::StartShoot()
{
    bIsAutomatic ? AutomaticShootStart() : PerformShoot();
}

//-----------------------------------------------------------------------------------------------
void UUShootComponent::EndShoot()
{
    if (bIsAutomatic)
        AutomaticShootEnd();
}

//-----------------------------------------------------------------------------------------------
void UUShootComponent::SwitchShootBehavior()
{
    bIsAutomatic = !bIsAutomatic;
}
#pragma endregion

#pragma region SHOOT METHODS
//-----------------------------------------------------------------------------------------------
void UUShootComponent::AutomaticShootStart()
{
   if(!GetWorld()->GetTimerManager().IsTimerActive(AutomaticShootTimerHandle))
       GetWorld()->GetTimerManager().SetTimer(AutomaticShootTimerHandle,this, &UUShootComponent::PerformShoot, FireRate, true, 0.f);
}

//-----------------------------------------------------------------------------------------------
void UUShootComponent::AutomaticShootEnd()
{
    if (GetWorld()->GetTimerManager().IsTimerActive(AutomaticShootTimerHandle))
        GetWorld()->GetTimerManager().ClearTimer(AutomaticShootTimerHandle);
    
    SpreadAngle = SpreadAngleMin;
}

//-----------------------------------------------------------------------------------------------
void UUShootComponent::PerformShoot() // Mover A RPC
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if (!PlayerController) return;

    APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;

    if (!CameraManager) return;

    CalculateSpread();

    const FVector StartPosition = CameraManager->GetCameraLocation();
    const FVector ForwardVector = CameraManager->GetActorForwardVector();
    const FVector EndPosition = StartPosition + ForwardVector * ShootDistance;


    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(GetOwner());
    ActorsToIgnore.Add(OwnerPlayer);


    for (int32 i = 0; i < NumberOfBullets; ++i)
    {
        float RandomYaw = FMath::RandRange(-SpreadAngle, SpreadAngle);

        float RandomPitch = FMath::RandRange(0.f, SpreadAngle);

        FRotator SpreadRotator = FRotator(-RandomPitch, RandomYaw, 0.f);
        FVector SpreadDirection = SpreadRotator.RotateVector(ForwardVector);

        FHitResult HitResult;
        UKismetSystemLibrary::SphereTraceSingle(
            this,
            StartPosition,
            StartPosition + SpreadDirection * ShootDistance,
            ShootRadius,
            ETraceTypeQuery::TraceTypeQuery1,
            false,
            ActorsToIgnore,
            EDrawDebugTrace::ForDuration,
            HitResult,
            true
        );

        if (HitResult.bBlockingHit)
        {
            UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), DamagePerBullet, HitResult.Location, HitResult, PlayerController, OwnerPlayer, UDamageType::StaticClass());
        }
    }
}
#pragma endregion

#pragma region SPREAD METHODS
//-----------------------------------------------------------------------------------------------
void UUShootComponent::CalculateSpread()
{
    bIsAutomatic ? CalculateAutomaticSpread() : CalculateSemiAutomaticSpread();
}

//-----------------------------------------------------------------------------------------------
void UUShootComponent::CalculateAutomaticSpread()
{
    SpreadAngle += SpreadPreShootIncrease;
    SpreadAngle = FMath::Clamp(SpreadAngle, SpreadAngleMin, SpreadAngleMax);
}

//-----------------------------------------------------------------------------------------------
void UUShootComponent::CalculateSemiAutomaticSpread()
{
    auto currentShootTIme = UGameplayStatics::GetRealTimeSeconds(GetWorld());

    TimeShootDiff = currentShootTIme - LastShootTime;

    if (TimeShootDiff < FireRate)
    {
        SpreadAngle += SpreadPreShootIncrease;
        SpreadAngle = FMath::Clamp(SpreadAngle, SpreadAngleMin, SpreadAngleMax);
    }
    else
    {
        SpreadAngle = SpreadAngleMin;
    }

    LastShootTime = currentShootTIme;
}
#pragma endregion