#include "GoalAIPawn.h"
#include "CombatAction.h"
#include "SubgoalAction.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"



AGoalAIPawn::AGoalAIPawn()
{
	CurrentCombatAction = nullptr;
	CurrentSubgoal = nullptr;
	bIsCombatActionComplete = true;
	bAreSubgoalsComplete = false;
	CurrentState = EGoalAIState::Idle;
	TurnCount = 0;
	bIsSubgoalComplete = false;
	PrimaryActorTick.bCanEverTick = true;
}

void AGoalAIPawn::BeginPlay()
{
	Super::BeginPlay();

	if (TurnLimit < 0)
	{
		TurnLimit = 0;
	}

	// Initialize or reset any AI state if needed here
	ResetAIState();
}

void AGoalAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentState)
	{
	case EGoalAIState::ExecutingCombatAction:
		if (CurrentCombatAction && !bIsCombatActionComplete)
		{
			CurrentCombatAction->CombatTick(this, DeltaTime);
		}
		break;

	case EGoalAIState::ExecutingSubgoals:
		if (CurrentSubgoal && !bIsSubgoalComplete)
		{
			CurrentSubgoal->TickSubgoal(this, DeltaTime);
		}
		break;

	case EGoalAIState::Idle:
	default:
		break;
	}
}

TStatId AGoalAIPawn::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(AGoalAIPawn, STATGROUP_Tickables);
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
