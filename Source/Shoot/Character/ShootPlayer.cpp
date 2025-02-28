/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "ShootPlayer.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Camera/CameraComponent.h>
#include "Components/CapsuleComponent.h"
#include "Shoot/Interfaces/IInteractable.h"
#include "Shoot/GameObjects/UsableObject.h"
#include <Shoot/Framework/ShootController.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <EnhancedInputComponent.h>

//-----------------------------------------------------------------------------------------------
AShootPlayer::AShootPlayer() : TraceDistance(1000.f)
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); 
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetupAttachment(FirstPersonCameraComponent);
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;
	GetMesh()->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::BeginPlay()
{
	Super::BeginPlay();
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawTraceLine();
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::GetUsableItem(TSubclassOf<class AUsableObject> UsableItem)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Get Usable"));
	
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;

	CurrentUsable = GetWorld()->SpawnActor<AUsableObject>(UsableItem, SpawnLocation, SpawnRotation);
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AShootPlayer::IputActionSprint);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AShootPlayer::IputActionSprint);

		// Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AShootPlayer::IputActionCrouch);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AShootPlayer::IputActionCrouch);

		// Primary Action
		EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Started, this, &AShootPlayer::IputActionPrimaryStart);

		EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Completed, this, &AShootPlayer::IputActionPrimaryEnd);

		// Secondary Action
		EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Started, this, &AShootPlayer::IputActionSecondaryStart);

		EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Completed, this, &AShootPlayer::IputActionSecondaryEnd);
	}
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::InputMoveSides(double value)
{
	AddMovementInput(GetActorRightVector(), value);
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::InputLook(FVector2D value)
{
	Super::InputLook(value);

	AddControllerYawInput(value.X);
	AddControllerPitchInput(value.Y);
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::InputInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interact Action"));
	if (CurretnInteractable)
		CurretnInteractable->Interact(this);
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::InputJump()
{
	Jump();
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::IputActionSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = Value.Get<bool>() ? 600.f : 400.f;
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::IputActionCrouch(const FInputActionValue& Value)
{
	Value.Get<bool>() ? Crouch() : UnCrouch();
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::IputActionPrimaryStart(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Primary Action"));
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::IputActionPrimaryEnd(const FInputActionValue& Value)
{
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::IputActionSecondaryStart(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Secondary Action"));

	if(CurrentUsable)
		CurrentUsable->SecondaryActionStart();
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::IputActionSecondaryEnd(const FInputActionValue& Value)
{
	if (CurrentUsable)
		CurrentUsable->SecondaryActionEnd();
}

//-----------------------------------------------------------------------------------------------
void AShootPlayer::DrawTraceLine()
{
	const FVector StartPosition = FirstPersonCameraComponent->GetComponentLocation();
	const FVector EndPosition = FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector() * TraceDistance;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	FHitResult HitResult;

	UKismetSystemLibrary::SphereTraceSingle(this, StartPosition, EndPosition, 8.f, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResult, true);

	if (auto HittedActor = Cast<IIInteractable>(HitResult.GetActor())) 
	{
		CurretnInteractable = HittedActor;
	}
}