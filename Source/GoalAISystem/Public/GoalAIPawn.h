// GoalAIPawn.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CombatAction.h"
#include "SubgoalAction.h"
#include "Tickable.h"
#include "GoalAIPawn.generated.h"

UENUM(BlueprintType)
enum class EGoalAIState : uint8
{
	Idle,
	ExecutingCombatAction,
	ExecutingSubgoals
};

UCLASS()
class AGoalAIPawn : public APawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	// To store the parent and children classes of Combat actions
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Combat")
	TArray<UCombatAction*> CombatActions{};

	// To store the parent and children classes of Subgoal actions
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Subgoal")
	TArray<USubgoalAction*> SubgoalActions{};
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
	EGoalAIState CurrentState = EGoalAIState::Idle;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Combat")
	TObjectPtr<UCombatAction> CurrentCombatAction = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Subgoal")
	TObjectPtr<USubgoalAction> CurrentSubgoal = nullptr;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
	bool bIsCombatActionComplete = true;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
	bool bAreSubgoalsComplete = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Subgoal")
	bool bIsSubgoalComplete = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subgoal")
	int32 TurnCount = 0;
	
	UFUNCTION(BlueprintCallable)
	void ResetAIState();

	UFUNCTION(BlueprintSetter, Category = "Subgoal")
	void SetTurnLimit(const int32 Limit) { TurnLimit = Limit < 0 ? 0 : Limit;}
	int32 GetTurnLimit() const {return TurnLimit;}
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Subgoal")
	int32 TurnLimit = 3;

	void BeginCombatAction();
	void BeginSubgoals();
	void AdvanceSubgoal();
};

