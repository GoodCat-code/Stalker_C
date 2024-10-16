#pragma once

#include "AWeapon.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Logging/LogMacros.h"
#include "Stalker_Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

//-------------------------------------------------------------------------------------------------------------
UCLASS(config=Game)
class AStalker_Character : public ACharacter
{
	GENERATED_BODY()

public:
	AStalker_Character();
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true")) USkeletalMeshComponent *Mesh_1P; // Pawn mesh: 1st person view (arms; seen only by self)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) AWeapon *Current_Weapon;

protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent *input_component);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<AActor *> Interactable_Actors; // Items which player can to interact

private:
	void On_Action_Move(const FInputActionValue &value); // Called for movement input
	void On_Action_Look(const FInputActionValue &value); // Called for looking input
	void On_Action_Fire(const FInputActionValue &value); // Called for fire input
	void On_Action_Use(const FInputActionValue &value); // Called for use input

	bool Pickup_Weapon(AWeapon *weapon);	// Attaches the weapon to a FirstPersonCharacter

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) UCameraComponent *FirstPersonCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Action_Jump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Action_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Action_Look;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Action_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *Action_Use;
};
//-------------------------------------------------------------------------------------------------------------
