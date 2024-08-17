#include "TP_Weapon_Component.h"
#include "Stalker_Character.h"
#include "Stalker_Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"

//-------------------------------------------------------------------------------------------------------------
UTP_WeaponComponent::UTP_WeaponComponent()
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);	// Default offset from the character location for projectiles to spawn
}
//-------------------------------------------------------------------------------------------------------------
bool UTP_WeaponComponent::AttachWeapon(AStalker_Character *target_character)
{
	Character = target_character;

	// Check that the character is valid, and has no weapon component yet
	if (Character == 0 || Character->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>())
		return false;

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->Mesh_1P, attachment_rules, FName(TEXT("GripPoint")));

	Character->AddInstanceComponent(this);	// add the weapon as an instance component to the character

	// Set up action bindings
	if (APlayerController *player_controller = Cast<APlayerController>(Character->GetController()) )
	{
		if (UEnhancedInputLocalPlayerSubsystem *input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()))
			input_subsystem->AddMappingContext(FireMappingContext, 1);	//Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input

		if (UEnhancedInputComponent *enhanced_input_component = Cast<UEnhancedInputComponent>(player_controller->InputComponent))
			enhanced_input_component->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);	// Fire
	}

	return true;
}
//-------------------------------------------------------------------------------------------------------------
void UTP_WeaponComponent::Fire()
{
	if (Character == 0 || Character->GetController() == 0)
		return;

	// Try and fire a projectile
	if (ProjectileClass != 0)
	{
		if (UWorld *world = GetWorld() )
		{
			APlayerController *player_controller = Cast<APlayerController>(Character->GetController());
			FRotator spawn_rotation = player_controller->PlayerCameraManager->GetCameraRotation();
			FVector spawn_location = GetOwner()->GetActorLocation() + spawn_rotation.RotateVector(MuzzleOffset); // MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position

			//Set Spawn Collision Handling Override
			FActorSpawnParameters actor_spawn_params;
			actor_spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			world->SpawnActor<AStalker_Projectile>(ProjectileClass, spawn_location, spawn_rotation, actor_spawn_params);	// Spawn the projectile at the muzzle
		}
	}
	if (FireSound != 0)
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());	// Try and play the sound if specified
	
	if (FireAnimation != 0)
		if (UAnimInstance *anim_instance = Character->Mesh_1P->GetAnimInstance() )
			anim_instance->Montage_Play(FireAnimation, 1.0f);	// Try and play a firing animation if specified
}
//-------------------------------------------------------------------------------------------------------------
void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type end_play_reason)
{
	if (Character == 0)
		return;

	if (APlayerController *player_controller = Cast<APlayerController>(Character->GetController()) )
		if (UEnhancedInputLocalPlayerSubsystem *input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller->GetLocalPlayer()) )
			input_subsystem->RemoveMappingContext(FireMappingContext);
}
//-------------------------------------------------------------------------------------------------------------
