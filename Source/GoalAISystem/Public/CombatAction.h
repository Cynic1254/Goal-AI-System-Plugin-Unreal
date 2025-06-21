#pragma once

#include "CoreMinimal.h"
#include "CombatAction.generated.h"

class AGoalAIPawn;

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class UCombatAction : public UObject
{
	GENERATED_BODY()

public:
	// Called when the subgoal is selected to begin
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void CombatStart(AGoalAIPawn* AIPawn);
	virtual void CombatStart_Implementation(AGoalAIPawn* AIPawn) {};

	// Virtual tick to be called from the pawn
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void CombatTick(AGoalAIPawn* AIPawn, float DeltaTime);
	virtual void CombatTick_Implementation(AGoalAIPawn* AIPawn, float DeltaTime) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FString Name = TEXT("DefaultCombatAction");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Weight = 1.0f;
};
