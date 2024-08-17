#include "Stalker_Player_Controller.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
//-------------------------------------------------------------------------------------------------------------
void AStalker_Player_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem *input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		input_subsystem->AddMappingContext(InputMappingContext, 0); 	// get the enhanced input subsystem
}
//-------------------------------------------------------------------------------------------------------------
