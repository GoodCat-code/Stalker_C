#include "TP_PickUp_Component.h"
//-------------------------------------------------------------------------------------------------------------
UTP_Pick_UpComponent::UTP_Pick_UpComponent()
{
	SphereRadius = 32.0f;	// Setup the Sphere Collision
}
//-------------------------------------------------------------------------------------------------------------
void UTP_Pick_UpComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UTP_Pick_UpComponent::On_Sphere_Begin_Overlap);	// Register our Overlap Event
}
//-------------------------------------------------------------------------------------------------------------
void UTP_Pick_UpComponent::On_Sphere_Begin_Overlap(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int other_body_index, bool from_sweep, const FHitResult &sweep_result)
{
	// Checking if it is a First Person character overlapping
	AStalker_Character *character = Cast<AStalker_Character>(other_actor);
	if (character != 0)
	{
		On_Pick_Up.Broadcast(character);		// Notify that the actor is being picked up
		OnComponentBeginOverlap.RemoveAll(this);		// Unregister from the Overlap Event so it is no longer triggered
	}
}
//-------------------------------------------------------------------------------------------------------------
