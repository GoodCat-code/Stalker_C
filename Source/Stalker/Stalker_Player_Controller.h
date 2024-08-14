#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "Stalker_Player_Controller.generated.h"

//-------------------------------------------------------------------------------------------------------------
UCLASS()
class STALKER_API AStalker_Player_Controller : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputMappingContext *InputMappingContext;	//Input Mapping Context to be used for player input

	virtual void BeginPlay() override;
};
//-------------------------------------------------------------------------------------------------------------
