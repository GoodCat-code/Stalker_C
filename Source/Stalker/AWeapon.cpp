#include "AWeapon.h"
#include "Stalker_Character.h"
#include "Engine/SkeletalMeshSocket.h"

//-------------------------------------------------------------------------------------------------------------
AWeapon::AWeapon()
{
	Muzzle_Offset = FVector(100.0f, 0.0f, 10.0f);	// Default offset from the character location for projectiles to spawn
}
//-------------------------------------------------------------------------------------------------------------
void AWeapon::Attach(USkeletalMeshComponent *arms_mesh)
{	
	USceneComponent *root_component = GetRootComponent();
	if (UPrimitiveComponent *prim_component = Cast<UPrimitiveComponent>(root_component) )
	{
		prim_component->SetSimulatePhysics(false);
		prim_component->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(arms_mesh, attachment_rules, FName(TEXT("GripPoint")));
}
//-------------------------------------------------------------------------------------------------------------
void AWeapon::Detach()
{
	USceneComponent *root_component = GetRootComponent();
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	if (UPrimitiveComponent *prim_component = Cast<UPrimitiveComponent>(root_component) )
	{
		prim_component->SetSimulatePhysics(true);
		prim_component->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	}
}
//-------------------------------------------------------------------------------------------------------------
void AWeapon::Attach_To_Socket(USkeletalMeshComponent *character_mesh, FName arm_socket_name)
{	
	USceneComponent *root_component = GetRootComponent();
	if (UPrimitiveComponent *prim_component = Cast<UPrimitiveComponent>(root_component) )
	{
		prim_component->SetSimulatePhysics(false);
		prim_component->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	}

	// Attach the weapon to the First Person Character
	//FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, true);
	//AttachToComponent(character_mesh, attachment_rules, arm_socket_name);

	if (const USkeletalMeshSocket *weapon_socket = character_mesh->GetSocketByName(arm_socket_name) )
		weapon_socket->AttachActor(this, character_mesh);
	else
		UE_LOG(LogTemp, Warning, TEXT("[%S]>>>>> No socket: %s"), __FUNCTION__, *(arm_socket_name.ToString() ) );
}
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
			FVector spawn_location = GetActorLocation() + spawn_rotation.RotateVector(Muzzle_Offset); // Muzzle_Offset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position

			//Set Spawn Collision Handling Override
			FActorSpawnParameters actor_spawn_params;
			actor_spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			world->SpawnActor<AStalker_Projectile>(Projectile_Class, spawn_location, spawn_rotation, actor_spawn_params);	// Spawn the projectile at the muzzle
		}
	}
	if (Fire_Sound != 0)
		UGameplayStatics::PlaySoundAtLocation(this, Fire_Sound, character->GetActorLocation());	// Try and play the sound if specified

	//if (Fire_Animation != 0)
	//{
	//	if (UAnimInstance *anim_instance = character->Mesh_1P->GetAnimInstance() )
	//		anim_instance->Montage_Play(Fire_Animation, 1.0f);	// Try and play a firing animation if specified
	//}
}
//-------------------------------------------------------------------------------------------------------------
void AWeapon::Fire_NPC()
{
	if (Fire_Animation != 0)
	{
		BP_Weapon_Mesh_Component->PlayAnimation(Fire_Animation, false);
	}
}
//-------------------------------------------------------------------------------------------------------------