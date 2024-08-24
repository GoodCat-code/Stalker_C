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

	UFUNCTION(BlueprintCallable, Category="Weapon") void Fire(AStalker_Character *character);	// Make the weapon Fire a Projectile

	UPROPERTY(EditDefaultsOnly, Category=Projectile) TSubclassOf<class AStalker_Projectile> Projectile_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) USoundBase *Fire_Sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage *Fire_Animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) FVector Muzzle_Offset; //Gun muzzle's offset from the characters location

};
//-------------------------------------------------------------------------------------------------------------
