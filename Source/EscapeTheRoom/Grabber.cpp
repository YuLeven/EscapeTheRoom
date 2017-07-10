// Yuri Levenhagen 2017

#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
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

	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The Physics Handle could not be found in %s"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UE_LOG(LogTemp, Warning, TEXT("Grab was called"));

	AActor* HitActor = HitResult.GetActor();

	if (HitActor)
	{
		FString ActorName = HitActor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Ray-cast hit: %s"), *ActorName);
		PhysicsHandle->GrabComponent(HitActor->GetRootPrimitiveComponent(), EName::NAME_None, HitActor->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("The user has release the key"));
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation = FVector();
	FRotator PlayerViewPointRotation = FRotator();

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/// Draw a red trace in the world to visualize
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast objects to report hit events
	FHitResult LineTraceHit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return LineTraceHit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GetGrabbedComponent())
	{
		FVector PlayerViewPointLocation = FVector();
		FRotator PlayerViewPointRotation = FRotator();

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerViewPointLocation,
			OUT PlayerViewPointRotation
		);

		/// Draw a red trace in the world to visualize
		FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

