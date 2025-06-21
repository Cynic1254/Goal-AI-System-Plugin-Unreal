#include "SubgoalAction.h"
#include "GoalAIPawn.h"

USubgoalAction::USubgoalAction()
{
	Name = TEXT("DefaultAction");
	Cost = 0;
}

void USubgoalAction::Initialize(const FString& name, const int32 cost)
{
	Name = name;
	Cost = cost;
}

USubgoalAction* USubgoalAction::Create(UObject* outer, const FString& name, int32 cost)
{
	USubgoalAction* NewAction = NewObject<USubgoalAction>(outer);
	if (NewAction)
	{
		NewAction->Initialize(name, cost);
	}
	return NewAction;
}