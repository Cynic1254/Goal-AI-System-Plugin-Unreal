#pragma once

#include "CoreMinimal.h"
#include "SubgoalAction.h"
#include "UtilityAI.generated.h"

class AGoalAIPawn;

UCLASS()
class UUtilityAI : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AI")
	static USubgoalAction* SelectBestAction(const TArray<USubgoalAction*>& SubgoalActions, AGoalAIPawn* AIPawn);
};
