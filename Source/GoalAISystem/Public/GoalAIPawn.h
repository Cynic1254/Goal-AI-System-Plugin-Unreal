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
class AGoalAIPawn : public APawn, public FTickableGameObject
{
	GENERATED_BODY()

public:
	AGoalAIPawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override { return true; }

	// To store the parent and children classes of Combat actions
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Combat")
	TArray<UCombatAction*> CombatActions;

	// To store the parent and children classes of Subgoal actions
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Subgoal")
	TArray<USubgoalAction*> SubgoalActions;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
	EGoalAIState CurrentState;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Combat")
	UCombatAction* CurrentCombatAction;

	UPROPERTY(BlueprintReadOnly, Category = "Subgoal")
	USubgoalAction* CurrentSubgoal;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
	bool bIsCombatActionComplete;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "State")
	bool bAreSubgoalsComplete;
	
	UPROPERTY(BlueprintReadOnly, Category = "Subgoal")
	bool bIsSubgoalComplete = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subgoal")
	int32 TurnCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subgoal")
	int32 TurnLimit = 3;
	
	UFUNCTION(BlueprintCallable)
	void ResetAIState();
};

