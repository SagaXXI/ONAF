// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveAroundRandomly.generated.h"

/**
 * 
 */
UCLASS()
class ONAF_API UMoveAroundRandomly : public UBTTaskNode
{
	GENERATED_BODY()

	UMoveAroundRandomly();
	
	//Called when this task node gets executed
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
