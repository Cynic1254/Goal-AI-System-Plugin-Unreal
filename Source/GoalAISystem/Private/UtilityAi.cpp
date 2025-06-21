#include "UtilityAi.h"

#include "GoalAIPawn.h"

USubgoalAction* UUtilityAI::SelectBestAction(const TArray<USubgoalAction*>& SubgoalActions, AGoalAIPawn* AIPawn)
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
