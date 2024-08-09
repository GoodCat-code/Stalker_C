#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Stalker_Character.h"
#include "TP_PickUpComponent.generated.h"
//-------------------------------------------------------------------------------------------------------------
// Declaration of the delegate that will be called when someone picks this up
// The character picking this up is the parameter sent with the notification
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOn_Pick_Up, AStalker_Character*, PickUpCharacter);
//-------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STALKER_API UTP_Pick_UpComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UTP_Pick_UpComponent();

	UPROPERTY(BlueprintAssignable, Category = "Interaction") FOn_Pick_Up On_Pick_Up;	// Delegate to whom anyone can subscribe to receive this event

protected:

	virtual void BeginPlay() override;	// Called when the game starts

	UFUNCTION() void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	//Code for when something overlaps this component
};
//-------------------------------------------------------------------------------------------------------------
