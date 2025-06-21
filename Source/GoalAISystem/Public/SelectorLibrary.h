#pragma once

#include "CoreMinimal.h"
#include "CombatAction.h"
#include "SubgoalAction.h"
#include "SelectorLibrary.generated.h"

class AGoalAIPawn;

UCLASS()
class USelectorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AI")
	static USubgoalAction* SelectBestAction(const TArray<USubgoalAction*>& SubgoalActions, AGoalAIPawn* AIPawn);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	static UCombatAction* SelectAction(const TArray<UCombatAction*>& CombatActions);
};
