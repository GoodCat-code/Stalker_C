#include "AWeapon.h"

//-------------------------------------------------------------------------------------------------------------
AWeapon::AWeapon()
{
	Muzzle_Offset = FVector(100.0f, 0.0f, 10.0f);	// Default offset from the character location for projectiles to spawn
}
//-------------------------------------------------------------------------------------------------------------
void AWeapon::Detach()
{
};
//-------------------------------------------------------------------------------------------------------------
void AWeapon::Fire(AStalker_Character *character)
{
	if (character == 0 || character->GetController() == 0)
		return;

	// Try and fire a projectile
	if (Projectile_Class != 0)
	{
		if (UWorld *world = GetWorld() )
		{
			APlayerController *player_controller = Cast<APlayerController>(character->GetController());
			FRotator spawn_rotation = player_controller->PlayerCameraManager->GetCameraRotation();
			FVector spawn_location = GetOwner()->GetActorLocation() + spawn_rotation.RotateVector(Muzzle_Offset); // Muzzle_Offset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position

			//Set Spawn Collision Handling Override
			FActorSpawnParameters actor_spawn_params;
			actor_spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			world->SpawnActor<AStalker_Projectile>(Projectile_Class, spawn_location, spawn_rotation, actor_spawn_params);	// Spawn the projectile at the muzzle
		}
	}
	if (Fire_Sound != 0)
		UGameplayStatics::PlaySoundAtLocation(this, Fire_Sound, character->GetActorLocation());	// Try and play the sound if specified

	if (Fire_Animation != 0)
		if (UAnimInstance *anim_instance = character->Mesh_1P->GetAnimInstance() )
			anim_instance->Montage_Play(Fire_Animation, 1.0f);	// Try and play a firing animation if specified

};
	//-------------------------------------------------------------------------------------------------------------