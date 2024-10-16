#pragma once

#include "Stalker_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "AWeapon.generated.h"
//-------------------------------------------------------------------------------------------------------------
UCLASS()
class STALKER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	void Attach(USkeletalMeshComponent *arms_mesh);
	void Detach();

	UFUNCTION(BlueprintCallable, Category="Weapon") void Attach_To_Socket(USkeletalMeshComponent *character_mesh, FName arm_socket_name);
	UFUNCTION(BlueprintCallable, Category="Weapon") void Fire(AStalker_Character *character);	// Make the weapon Fire a Projectile
	UFUNCTION(BlueprintCallable, Category="Weapon") void Fire_NPC();

	UPROPERTY(EditDefaultsOnly, Category=Projectile) TSubclassOf<class AStalker_Projectile> Projectile_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) USoundBase *Fire_Sound;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage *Fire_Animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimationAsset *Fire_Animation = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) FVector Muzzle_Offset; //Gun muzzle's offset from the characters location

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) USkeletalMeshComponent *BP_Weapon_Mesh_Component = 0;
};
//-------------------------------------------------------------------------------------------------------------
