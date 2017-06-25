// Yuri Levenhagen 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Function to open the door
	void OpenDoor();

	//Function to close the door
	void CloseDoor();

private:

	void YawDoor(float NewYaw);

	//The angle to open the door
	UPROPERTY(VisibleAnywhere, Category = "Doors")
	float OpenAngle;

	//The pressure plate which will cause the door to be opened if stepped upon
	UPROPERTY(EditAnywhere, Category = "Doors")
	class ATriggerVolume* PressurePlate;

	//The actor (in this case, the player) which causes the pressure trigger to fire a response
	UPROPERTY(EditAnywhere, Category = "Doors")
	class AActor* ActorToTriggerPressurePlate;

	//Helper function to termine if the door is alredy open
	FORCEINLINE bool IsDoorOpen(const FRotator Rotator) const { return Rotator.Yaw > 0; };

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay;

	UPROPERTY()
	float LastDoorOpenTime;

	class AActor* OwningActor;
	
};