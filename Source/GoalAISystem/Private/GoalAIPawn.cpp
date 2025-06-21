#include "GoalAIPawn.h"
#include "CombatAction.h"
#include "SelectorLibrary.h"
#include "SubgoalAction.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"

void AGoalAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentState)
	{
	case EGoalAIState::ExecutingCombatAction:
		if (bIsCombatActionComplete)
		{
			BeginSubgoals();
		}
		if (CurrentCombatAction && !bIsCombatActionComplete)
		{
			CurrentCombatAction->CombatTick(this, DeltaTime);
		}
		break;

	case EGoalAIState::ExecutingSubgoals:
		if (bIsSubgoalComplete)
		{
			AdvanceSubgoal();
		}
		if (CurrentSubgoal && !bIsSubgoalComplete)
		{
			CurrentSubgoal->TickSubgoal(this, DeltaTime);
		}
		break;

	case EGoalAIState::Idle:
		BeginCombatAction();
		break;
	default:
		break;
	}
}

void AGoalAIPawn::ResetAIState()
{
	CurrentCombatAction = nullptr;
	CurrentSubgoal = nullptr;
	bIsCombatActionComplete = true;
	bAreSubgoalsComplete = false;
	CurrentState = EGoalAIState::Idle;
	TurnCount = 0;
	bIsSubgoalComplete = false;
}

void AGoalAIPawn::BeginCombatAction()
{
	if (CombatActions.Num() == 0) return;

	UCombatAction* Best = nullptr;
	float TotalWeight = 0.f;

	for (UCombatAction* Action : CombatActions)
	{
		if (Action)
		{
			TotalWeight += Action->Weight;
		}
	}

	if (TotalWeight <= 0.f) return;

	float Roll = FMath::FRandRange(0.f, TotalWeight);
	float Accumulated = 0.f;

	for (UCombatAction* Action : CombatActions)
	{
		if (!Action) continue;
		Accumulated += Action->Weight;
		if (Roll <= Accumulated)
		{
			Best = Action;
			break;
		}
	}

	if (Best)
	{
		CurrentCombatAction = Best;
		CurrentState = EGoalAIState::ExecutingCombatAction;
		bIsCombatActionComplete = false;

		UE_LOG(LogTemp, Log, TEXT("Selected Combat Action: %s"), *Best->GetName());
		// Blueprint or system should now handle executing the combat action.

		Best->CombatStart(this);
	}
}

void AGoalAIPawn::BeginSubgoals()
{
	if (SubgoalActions.Num() == 0)
	{
		bAreSubgoalsComplete = true;
		CurrentState = EGoalAIState::Idle;
		return;
	}

	TurnCount = 0;
	bAreSubgoalsComplete = false;
	CurrentState = EGoalAIState::ExecutingSubgoals;

	AdvanceSubgoal();
}

void AGoalAIPawn::AdvanceSubgoal()
{
	// Add the cost of the last subgoal executed, if any
	if (CurrentSubgoal)
	{
		TurnCount += CurrentSubgoal->Cost;  // Assuming GetCost() exists on USubgoalAction
	}

	if (TurnCount >= GetTurnLimit())
	{
		// Reached turn limit, finish
		bAreSubgoalsComplete = true;
		CurrentSubgoal = nullptr;
		CurrentState = EGoalAIState::Idle;
		UE_LOG(LogTemp, Log, TEXT("Reached turn limit, subgoals complete for %s"), *GetName());
		return;
	}

	// Select best next subgoal
	USubgoalAction* BestSubgoal = USelectorLibrary::SelectBestAction(SubgoalActions, this);

	if (!BestSubgoal)
	{
		// No valid subgoal found, finish
		bAreSubgoalsComplete = true;
		CurrentSubgoal = nullptr;
		CurrentState = EGoalAIState::Idle;
		UE_LOG(LogTemp, Log, TEXT("No subgoals available, subgoals complete for %s"), *GetName());
		return;
	}

	// Execute the best subgoal
	CurrentSubgoal = BestSubgoal;
	bIsSubgoalComplete = false;
	BestSubgoal->StartSubgoal(this);

	UE_LOG(LogTemp, Log, TEXT("Started Subgoal: %s"), *BestSubgoal->GetName());
}
