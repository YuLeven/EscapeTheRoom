// Yuri Levenhagen 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Sets the angle of opening of the door
	OpenAngle = -90.f;
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Gets the player pawn and sets the ActorToTriggerPressurePlate property to a cast of it to AActor
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AActor* ActorToTriggerPressurePlate = Cast<AActor>(PlayerPawn);

}

void UOpenDoor::OpenDoor()
{
	//Gets the owner (the chair) and, if not already open, opens it
	AActor* Owner = GetOwner();
	if (Owner)
	{
		if (!IsDoorOpen(Owner->GetActorRotation()))
		{
			FRotator Rotator = FRotator(0.f, OpenAngle, 0.f);
			Owner->SetActorRotation(Rotator);
		}
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Opens the door if the trigger actor (the player) is overlapping the pressure plate
	if (ActorToTriggerPressurePlate && PressurePlate->IsOverlappingActor(ActorToTriggerPressurePlate))
	{
		OpenDoor();
	}
}

