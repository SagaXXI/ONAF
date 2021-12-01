// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AnimatronicsController.generated.h"

/**
 * 
 */
UCLASS()
class ONAF_API AAnimatronicsController : public AAIController
{
	GENERATED_BODY()

	AAnimatronicsController();

	UPROPERTY()
	class UBehaviorTreeComponent* BTComp;

	UPROPERTY()
	class UBlackboardComponent* BBComp;

	//Starter location of the animatronic
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName StartLocation;

	//Can animatronic move or not
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName CanMove;

	//Player pawn
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PlayerLocation;

	//Location to go to (Actually used to random movement around a small area, like patrolling)
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGo;

	//Is player dead
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName IsPlayerDead;

	//Called when the pawn gets possesed by this controller
	void OnPossess(APawn* InPawn) override;

public:

	//Called in case if the player was caught by the pawn sensing comp
	void SetPlayerCaught(FVector PawnLocation);

	FORCEINLINE UBehaviorTreeComponent* GetBTComp() {return BTComp;}

	FORCEINLINE UBlackboardComponent* GetBBComp() {return BBComp; }

	UPROPERTY(EditAnywhere, Category = "AI Movement")
	float MovementRadius = 2000.f;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "FX")
	bool IsFreddyThumped = false;

protected:

	UPROPERTY(EditAnywhere, Category = "AI Movement", meta = (BlueprintProtected = true))
	float MovementDelay = 5.f;
};
