#pragma once
#include "CoreMinimal.h"
#include <string>
#include "SubgoalAction.generated.h"

class AGoalAIPawn;

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class USubgoalAction : public UObject
{
	GENERATED_BODY()
	
public:
	USubgoalAction();

	UFUNCTION(BlueprintCallable, Category = "Subgoal")
	void Initialize(const FString& name, const int32 cost);

	UFUNCTION(BlueprintCallable, Category = "Subgoal")
	static USubgoalAction* Create(UObject* outer, const FString& name, int32 cost);

	// Called when the subgoal is selected to begin
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Subgoal")
	void StartSubgoal(AGoalAIPawn* AIPawn);
	virtual void StartSubgoal_Implementation(AGoalAIPawn* AIPawn){};

	// Tick that is called from the pawn 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Subgoal")
	void TickSubgoal(AGoalAIPawn* AIPawn, float DeltaTime);
	virtual void TickSubgoal_Implementation(AGoalAIPawn* AIPawn, float DeltaTime) {};

	// Called in order to calculate it's current utility score
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Subgoal")
	float CalculateUtility(AGoalAIPawn* AIPawn) const;
	virtual float CalculateUtility_Implementation(AGoalAIPawn* AIPawn) const {return 0.0f;}

	UFUNCTION(BlueprintCallable, Category = "Subgoal")
	FString GetName() { return Name; }

	UFUNCTION(BlueprintCallable, Category = "Subgoal")
	int32 GetCost() const { return Cost; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subgoal", meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subgoal", meta = (AllowPrivateAccess = "true"))
	int32 Cost;
};
