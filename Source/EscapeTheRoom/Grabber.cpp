// Yuri Levenhagen 2017

#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "PlayerViewPoints.h"
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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();

	SetupInputComponent();	
}

void UGrabber::SetupInputComponent()
{
	/// Look for the attached Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		//Bind the input axis
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The Input Component could not be found in %s"), *GetOwner()->GetName());
	}
}

void UGrabber::FindPhysicsHandle()
{
	/// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The Physics Handle could not be found in %s"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	AActor* HitActor = HitResult.GetActor();

	if (HitActor)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			Cast<UPrimitiveComponent>(HitActor->GetRootComponent()),
			EName::NAME_None,
			HitActor->GetActorLocation(),
			HitActor->GetActorRotation()
		);
	}
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast objects to report hit events
	FHitResult LineTraceHit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		GetPlayerReachLineTraceStart(),
		GetPlayerReachLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return LineTraceHit;
}

FVector UGrabber::GetPlayerReachLineTraceStart() const
{
	/// Returns the calculated player reach (represented by a Vector)
	return FPlayerViewPoints(GetWorld()).PlayerViewPointLocation;
}

FVector UGrabber::GetPlayerReachLineTraceEnd() const
{
	/// Returns the calculated player reach (represented by a Vector)
	FPlayerViewPoints PlayerViewPoints(GetWorld());
	return PlayerViewPoints.PlayerViewPointLocation + PlayerViewPoints.PlayerViewPointRotator.Vector() * Reach;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->SetTargetLocation(GetPlayerReachLineTraceEnd());
	}
}
