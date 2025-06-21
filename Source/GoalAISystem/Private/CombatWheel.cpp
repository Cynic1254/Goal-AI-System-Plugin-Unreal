#include "CombatWheel.h"
#include "Math/UnrealMathUtility.h"

UCombatAction* UCombatWheel::SelectAction(const TArray<UCombatAction*>& CombatActions)
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
			TotalWeight += Action->GetWeight();
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

		CumulativeWeight += Action->GetWeight();
		if (RandomValue <= CumulativeWeight)
		{
			return Action;
		}
	}

	return nullptr;
}
