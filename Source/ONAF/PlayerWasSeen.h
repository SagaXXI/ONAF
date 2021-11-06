// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PlayerWasSeen.generated.h"

/**
 * 
 */
UCLASS()
class ONAF_API UPlayerWasSeen : public UBTTaskNode
{
	GENERATED_BODY()

	//Called when this task node gets executed
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
