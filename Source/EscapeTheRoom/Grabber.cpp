// Yuri Levenhagen 2017

#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Engine.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//The distance which the player can grab stuff
	Reach = 100.f;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation = FVector();
	FRotator PlayerViewPointRotation = FRotator();

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), 
	//	*PlayerViewPointLocation.ToString(),
	//	*PlayerViewPointRotation.ToString()
	//);

	//Draw a red trace in the world to visualize
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);
	// ...
}

