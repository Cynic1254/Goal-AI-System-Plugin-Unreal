#pragma once

#include "CoreMinimal.h"
#include <string>
#include "CombatAction.generated.h"

class AGoalAIPawn;

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class UCombatAction : public UObject
{
	GENERATED_BODY()

public:
	
	UCombatAction();
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Initialize(const FString& name, float weight);

	// Called when the subgoal is selected to begin
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void CombatStart(AGoalAIPawn* AIPawn);
	virtual void CombatStart_Implementation(AGoalAIPawn* AIPawn) {};

	// Virtual tick to be called from the pawn
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void CombatTick(AGoalAIPawn* AIPawn, float DeltaTime);
	virtual void CombatTick_Implementation(AGoalAIPawn* AIPawn, float DeltaTime) {};

	UFUNCTION(BlueprintCallable, Category = "Combat")
	static UCombatAction* Create(UObject* Outer, const FString& InName, float InWeight);
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	FString GetName() { return Name; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	float GetWeight() const { return Weight; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Weight;
};
