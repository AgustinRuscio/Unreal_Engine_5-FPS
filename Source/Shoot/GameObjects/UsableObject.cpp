/* >---------------------------<
> Author: Agustin Ruscio
> UE Version: 5.5.3
>---------------------------< */

#include "UsableObject.h"

//-----------------------------------------------------------------------------------------------
AUsableObject::AUsableObject()
{
	PrimaryActorTick.bCanEverTick = true;

	ObjectMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Object Mesh");
}

//-----------------------------------------------------------------------------------------------
AShootBaseCharacter* AUsableObject::GetObjectOwner() const
{
	return ObjectOwner;
}