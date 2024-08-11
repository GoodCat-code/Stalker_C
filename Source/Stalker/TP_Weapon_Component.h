#pragma once

#include "Stalker_Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "InputMappingContext.h"
#include "TP_Weapon_Component.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STALKER_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UTP_WeaponComponent();

	UFUNCTION(BlueprintCallable, Category="Weapon") bool AttachWeapon(AStalker_Character *target_character);	// Attaches the weapon to a FirstPersonCharacter
	UFUNCTION(BlueprintCallable, Category="Weapon") void Fire();	// Make the weapon Fire a Projectile

	UPROPERTY(EditDefaultsOnly, Category=Projectile) TSubclassOf<class AStalker_Projectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) USoundBase *FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage *FireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) FVector MuzzleOffset; //Gun muzzle's offset from the characters location

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) UInputMappingContext *FireMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) UInputAction *FireAction;

protected:
	virtual void EndPlay(const EEndPlayReason::Type end_play_reason) override;

private:
	AStalker_Character *Character;	// The Character holding this weapon
};
//-------------------------------------------------------------------------------------------------------------
