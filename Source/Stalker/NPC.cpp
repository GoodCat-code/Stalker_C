#include "NPC.h"

// ANPC
//-------------------------------------------------------------------------------------------------------------
ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true; 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}
//-------------------------------------------------------------------------------------------------------------
void ANPC::BeginPlay()
{
	Super::BeginPlay();

}
//-------------------------------------------------------------------------------------------------------------
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//-------------------------------------------------------------------------------------------------------------




// ANPC_Human
//-------------------------------------------------------------------------------------------------------------
bool ANPC_Human::Attach_Weapon(USkeletalMeshComponent *character_mesh, FName arm_socket_name, AWeapon *weapon)
{

	if (weapon == 0)	// Check that the weapon is valid
	{
		UE_LOG(LogTemp, Warning, TEXT("[%S] >>>>> No weapon"), __FUNCTION__);
		return false;
	}

	if (Current_Weapon !=0)
		Current_Weapon->Detach();

	Current_Weapon = weapon;
	Current_Weapon->Attach_To_Socket(character_mesh, arm_socket_name);

	return true;
}
//-------------------------------------------------------------------------------------------------------------