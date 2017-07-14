// Yuri Levenhagen 2017

#include "PlayerViewPoints.h"
#include "Engine/World.h"

FPlayerViewPoints::FPlayerViewPoints()
{

}

FPlayerViewPoints::FPlayerViewPoints(UWorld* World)
{
	World->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotator
	);
}