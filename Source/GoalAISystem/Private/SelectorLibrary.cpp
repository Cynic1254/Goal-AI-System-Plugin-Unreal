#include "SelectorLibrary.h"

#include "GoalAIPawn.h"

USubgoalAction* USelectorLibrary::SelectBestAction(const TArray<USubgoalAction*>& SubgoalActions, AGoalAIPawn* AIPawn)
{
	if (SubgoalActions.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UtilityAI: No subgoal actions provided."));
		return nullptr;
	}

	float BestUtility = -1.0f;
	USubgoalAction* BestAction = nullptr;

	for (USubgoalAction* Action : SubgoalActions)
	{
		if (!IsValid(Action)) continue;
		
		const float Utility = Action->CalculateUtility(AIPawn);

		UE_LOG(LogTemp, Log, TEXT("Evaluated subgoal %s with utility %.2f"), *Action->GetName(), Utility);
		
		if (Utility > BestUtility)
		{
			BestUtility = Utility;
			BestAction = Action;
		}
	}

	if (BestAction)
	{
		UE_LOG(LogTemp, Log, TEXT("Selected best subgoal: %s (Utility: %.2f)"), *BestAction->GetName(), BestUtility);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UtilityAI: No valid subgoal actions found."));
	}
	
	return BestAction;
}

UCombatAction* USelectorLibrary::SelectAction(const TArray<UCombatAction*>& CombatActions)
{
	if (CombatActions.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("CombatWheel: No combat actions provided."));
		return nullptr;
	}

	float TotalWeight = 0.0f;

	for (const UCombatAction* Action : CombatActions)
	{
		if (IsValid(Action))
		{
			TotalWeight += Action->Weight;
		}
	}

	if (TotalWeight <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("CombatWheel: Total weight is zero or negative."));
		return nullptr;
	}

	const float RandomValue = FMath::FRandRange(0.0f, TotalWeight);
	float CumulativeWeight = 0.0f;

	for (UCombatAction* Action : CombatActions)
	{
		if (!IsValid(Action)) continue;

		CumulativeWeight += Action->Weight;
		if (RandomValue <= CumulativeWeight)
		{
			return Action;
		}
	}

	return nullptr;
}