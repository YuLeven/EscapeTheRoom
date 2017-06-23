// Yuri Levenhagen 2017

#include "PositionReporter.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();
	// ...
	FVector Location = GetOwner()->GetActorTransform().GetLocation();
	FString Name = GetOwner()->GetName();
	FString Coordinates = FString::Printf(TEXT("X: %f, Y: %f, Z: %f"), Location.X, Location.Y, Location.Z);

	UE_LOG(LogTemp, Warning, TEXT("%s is located at: %s"), *Name, *Coordinates);
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

