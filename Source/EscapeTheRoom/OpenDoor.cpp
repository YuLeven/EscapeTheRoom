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
	
	//The time to be elapse until the door is automatically closed
	DoorCloseDelay = 0.8f;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Gets the player pawn and sets the ActorToTriggerPressurePlate property to a cast of it to AActor
	ActorToTriggerPressurePlate = UGameplayStatics::GetPlayerPawn(this, 0);
	OwningActor = GetOwner();
}

void UOpenDoor::YawDoor(float NewYaw)
{
	if (OwningActor)
	{
		OwningActor->SetActorRotation(FRotator(0.f, NewYaw, 0.f));
	}
}

//Opens the door by setting it's yaw value to the value set by either the class or the GD on the editor
void UOpenDoor::OpenDoor()
{
	YawDoor(OpenAngle);
}

//Closes the door by settings it's yaw value to zero
void UOpenDoor::CloseDoor()
{
	YawDoor(0.f);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float CurrentTime = GetWorld()->GetTimeSeconds();

	//Opens the door if the trigger actor (the player) is overlapping the pressure plate
	if (ActorToTriggerPressurePlate && PressurePlate->IsOverlappingActor(ActorToTriggerPressurePlate))
	{
		OpenDoor();
		LastDoorOpenTime = CurrentTime;
	}
	//Check if it's time to close the door
	else if (LastDoorOpenTime && (CurrentTime - LastDoorOpenTime) >= DoorCloseDelay)
	{
		CloseDoor();
	}

}

