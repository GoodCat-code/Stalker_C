#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Logging/LogMacros.h"
#include "Stalker_Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
//class UInputAction;
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
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction *LookAction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true")) USkeletalMeshComponent *Mesh_1P; // Pawn mesh: 1st person view (arms; seen only by self)

protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent *input_component);

	void Move(const FInputActionValue &value); // Called for movement input
	void Look(const FInputActionValue &value); // Called for looking input

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) UCameraComponent *FirstPersonCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) UInputAction *JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) UInputAction *MoveAction;
};
//-------------------------------------------------------------------------------------------------------------
