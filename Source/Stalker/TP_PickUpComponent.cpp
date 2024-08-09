#include "TP_PickUpComponent.h"
//-------------------------------------------------------------------------------------------------------------
UTP_Pick_UpComponent::UTP_Pick_UpComponent()
{
	SphereRadius = 32.0f;	// Setup the Sphere Collision
}
//-------------------------------------------------------------------------------------------------------------
void UTP_Pick_UpComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UTP_Pick_UpComponent::OnSphereBeginOverlap);	// Register our Overlap Event
}
//-------------------------------------------------------------------------------------------------------------
void UTP_Pick_UpComponent::OnSphereBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AStalker_Character *Character = Cast<AStalker_Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		On_Pick_Up.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
//-------------------------------------------------------------------------------------------------------------
