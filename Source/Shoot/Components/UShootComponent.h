/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UShootComponent.generated.h"

UENUM(BlueprintType)
enum class EShootType : uint8
{
	EST_SemiAutomatic,
	EST_Automatic,
	EST_Burst
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOT_API UUShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUShootComponent();

	//------------------------------------------------------------------//
	//							Public Methods							//
	//------------------------------------------------------------------//
	void SetOwner(AActor* WeaponOwner);

	void StartShoot();
	void EndShoot();
	void SwitchShootBehavior();

	//------------------------------------------------------------------//
	//							Public Variables						//
	//------------------------------------------------------------------//

private:
	//------------------------------------------------------------------//
	//							Private Methods							//
	//------------------------------------------------------------------//
	void AutomaticShootStart();
	void AutomaticShootEnd();

	void BurstShoot();

	void PerformShoot();

	void CalculateSpread();
	void CalculateAutomaticSpread();
	void CalculateSemiAutomaticSpread();

	//------------------------------------------------------------------//
	//							Private Variables						//
	//------------------------------------------------------------------//
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	int NumberOfBullets = 1;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	int BurstAmount = 3;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float ShootDistance = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float FireRate = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float SpreadAngleMin = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float SpreadAngleMax = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float SpreadPreShootIncrease = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float ShootRadius = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float DamagePerBullet = 10.f;

	float LastShootTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	EShootType PrimaryShootType;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	EShootType SecondaryShootType;

	AActor* OwnerPlayer;

	FTimerHandle AutomaticShootTimerHandle;
	FTimerHandle BurstShootTimerHandle;
};