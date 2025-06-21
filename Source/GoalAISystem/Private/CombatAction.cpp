#include "CombatAction.h"

#include "GoalAIPawn.h"

UCombatAction::UCombatAction()
{
	Name = TEXT("DefaultCombatAction");
	Weight = 1.0f;
}

void UCombatAction::Initialize(const FString& InName, float InWeight)
{
	Name = InName;
	Weight = InWeight;
}

UCombatAction* UCombatAction::Create(UObject* Outer, const FString& InName, float InWeight)
{
	UCombatAction* NewObj = NewObject<UCombatAction>(Outer);
	if (NewObj)
	{
		NewObj->Initialize(InName, InWeight);
	}
	return NewObj;
}
