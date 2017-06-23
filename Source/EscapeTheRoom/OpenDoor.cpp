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

	// ...

}

void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		FRotator Rotator = FRotator(0.f, OpenAngle, 0.f);
		Owner->SetActorRotation(Rotator);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Rotator is undefined"));
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AActor* PlayerActor = Cast<AActor>(PlayerPawn);
	
	if (PlayerActor)
	{
		if (PressurePlate->IsOverlappingActor(PlayerActor))
		{
			OpenDoor();
		}
	}

	// ...
}

