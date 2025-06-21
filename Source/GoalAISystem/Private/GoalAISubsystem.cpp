#include "GoalAISubsystem.h"
#include "EngineUtils.h"
#include "GoalAIPawn.h"
#include "CombatAction.h"
#include "SubgoalAction.h"
#include "UtilityAi.h"

void UGoalAISubsystem::Tick(float DeltaTime)
{
	const UWorld* World = GetWorld();
	if (!World || World->WorldType != EWorldType::Game && World->WorldType != EWorldType::PIE)
	{
		return; // skip ticking in editor or when world is not valid
	}
	
	for (TActorIterator<AGoalAIPawn> It(World); It; ++It)
	{
		ProcessAIPawn(*It);
	}
}

TStatId UGoalAISubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UGoalAISubsystem, STATGROUP_Tickables);
}

void UGoalAISubsystem::ProcessAIPawn(AGoalAIPawn* AIPawn)
{
	if (!IsValid(AIPawn)) return;

	switch (AIPawn->CurrentState)
	{
	case EGoalAIState::Idle:
		BeginCombatAction(AIPawn);
		break;

	case EGoalAIState::ExecutingCombatAction:
		if (AIPawn->bIsCombatActionComplete)
		{
			BeginSubgoals(AIPawn);
		}
		break;

	case EGoalAIState::ExecutingSubgoals:
		if (AIPawn->bIsSubgoalComplete)
		{
			AdvanceSubgoal(AIPawn);
		}
		break;

	default:
		break;
	}
}

void UGoalAISubsystem::BeginCombatAction(AGoalAIPawn* AIPawn)
{
	if (AIPawn->CombatActions.Num() == 0) return;

	UCombatAction* Best = nullptr;
	float TotalWeight = 0.f;

	for (UCombatAction* Action : AIPawn->CombatActions)
	{
		if (Action)
		{
			TotalWeight += Action->GetWeight();
		}
	}

	if (TotalWeight <= 0.f) return;

	float Roll = FMath::FRandRange(0.f, TotalWeight);
	float Accumulated = 0.f;

	for (UCombatAction* Action : AIPawn->CombatActions)
	{
		if (!Action) continue;
		Accumulated += Action->GetWeight();
		if (Roll <= Accumulated)
		{
			Best = Action;
			break;
		}
	}

	if (Best)
	{
		AIPawn->CurrentCombatAction = Best;
		AIPawn->CurrentState = EGoalAIState::ExecutingCombatAction;
		AIPawn->bIsCombatActionComplete = false;

		UE_LOG(LogTemp, Log, TEXT("Selected Combat Action: %s"), *Best->GetName());
		// Blueprint or system should now handle executing the combat action.

		Best->CombatStart(AIPawn);
	}
}

void UGoalAISubsystem::BeginSubgoals(AGoalAIPawn* AIPawn)
{
	if (AIPawn->SubgoalActions.Num() == 0)
	{
		AIPawn->bAreSubgoalsComplete = true;
		AIPawn->CurrentState = EGoalAIState::Idle;
		return;
	}

	AIPawn->TurnCount = 0;
	AIPawn->bAreSubgoalsComplete = false;
	AIPawn->CurrentState = EGoalAIState::ExecutingSubgoals;

	AdvanceSubgoal(AIPawn);
}

void UGoalAISubsystem::AdvanceSubgoal(AGoalAIPawn* AIPawn)
{
	// Add the cost of the last subgoal executed, if any
	if (AIPawn->CurrentSubgoal)
	{
		AIPawn->TurnCount += AIPawn->CurrentSubgoal->GetCost();  // Assuming GetCost() exists on USubgoalAction
	}

	if (AIPawn->TurnCount >= AIPawn->TurnLimit)
	{
		// Reached turn limit, finish
		AIPawn->bAreSubgoalsComplete = true;
		AIPawn->CurrentSubgoal = nullptr;
		AIPawn->CurrentState = EGoalAIState::Idle;
		UE_LOG(LogTemp, Log, TEXT("Reached turn limit, subgoals complete for %s"), *AIPawn->GetName());
		return;
	}

	// Select best next subgoal
	USubgoalAction* BestSubgoal = UUtilityAI::SelectBestAction(AIPawn->SubgoalActions, AIPawn);

	if (!BestSubgoal)
	{
		// No valid subgoal found, finish
		AIPawn->bAreSubgoalsComplete = true;
		AIPawn->CurrentSubgoal = nullptr;
		AIPawn->CurrentState = EGoalAIState::Idle;
		UE_LOG(LogTemp, Log, TEXT("No subgoals available, subgoals complete for %s"), *AIPawn->GetName());
		return;
	}

	// Execute the best subgoal
	AIPawn->CurrentSubgoal = BestSubgoal;
	AIPawn->bIsSubgoalComplete = false;
	BestSubgoal->StartSubgoal(AIPawn);

	UE_LOG(LogTemp, Log, TEXT("Started Subgoal: %s"), *BestSubgoal->GetName());
}
