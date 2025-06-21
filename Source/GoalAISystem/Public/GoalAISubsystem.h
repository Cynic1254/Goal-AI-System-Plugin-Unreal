#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Tickable.h"
#include "GoalAISubsystem.generated.h"

class AGoalAIPawn;
class UCombatAction;
class USubgoalAction;

UCLASS()
class UGoalAISubsystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override { return true; }

private:
	void ProcessAIPawn(AGoalAIPawn* AIPawn);
	void BeginCombatAction(AGoalAIPawn* AIPawn);
	void BeginSubgoals(AGoalAIPawn* AIPawn);
	void AdvanceSubgoal(AGoalAIPawn* AIPawn);
};

