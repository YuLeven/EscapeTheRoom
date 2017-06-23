// Yuri Levenhagen 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:

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
	FORCEINLINE bool IsDoorOpen(FRotator Rotator) const { return Rotator.Yaw > 0; };

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Function to open the door if possible
	void OpenDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
