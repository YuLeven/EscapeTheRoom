// Yuri Levenhagen 2017

#pragma once

#include "CoreMinimal.h"
#include "PlayerViewPoints.generated.h"

USTRUCT()
struct ESCAPETHEROOM_API FPlayerViewPoints
{
	GENERATED_BODY()

public:

	FPlayerViewPoints();

	FPlayerViewPoints(class UWorld* World);

	UPROPERTY()
	FRotator PlayerViewPointRotator;

	UPROPERTY()
	FVector PlayerViewPointLocation;
};

