#pragma once
#include "CoreMinimal.h"
#include "SubgoalAction.generated.h"

class AGoalAIPawn;

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class USubgoalAction : public UObject
{
	GENERATED_BODY()
	
public:
	// Called when the subgoal is selected to begin
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Subgoal")
	void StartSubgoal(AGoalAIPawn* AIPawn);
	virtual void StartSubgoal_Implementation(AGoalAIPawn* AIPawn){}

	// Tick that is called from the pawn 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Subgoal")
	void TickSubgoal(AGoalAIPawn* AIPawn, float DeltaTime);
	virtual void TickSubgoal_Implementation(AGoalAIPawn* AIPawn, float DeltaTime) {}

	// Called in order to calculate it's current utility score
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Subgoal")
	float CalculateUtility(AGoalAIPawn* AIPawn) const;
	virtual float CalculateUtility_Implementation(AGoalAIPawn* AIPawn) const {return 0.0f;}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subgoal")
	FString Name = TEXT("DefaultAction");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subgoal")
	int32 Cost = 0;
};
