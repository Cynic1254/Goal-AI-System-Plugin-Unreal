#pragma once

#include "CoreMinimal.h"
#include "CombatAction.h"
#include "CombatWheel.generated.h"

UCLASS()
class UCombatWheel : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	static UCombatAction* SelectAction(const TArray<UCombatAction*>& CombatActions);
};
