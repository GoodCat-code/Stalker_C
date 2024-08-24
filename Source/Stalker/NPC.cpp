#include "NPC.h"
//-------------------------------------------------------------------------------------------------------------
ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true; 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}
//-------------------------------------------------------------------------------------------------------------
void ANPC::BeginPlay()
{
	Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//-------------------------------------------------------------------------------------------------------------
