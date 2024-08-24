#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"
//-------------------------------------------------------------------------------------------------------------
UCLASS()
class STALKER_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
//-------------------------------------------------------------------------------------------------------------
UCLASS()
class STALKER_API ANPC_Human : public ANPC
{
	GENERATED_BODY()
};
//-------------------------------------------------------------------------------------------------------------
