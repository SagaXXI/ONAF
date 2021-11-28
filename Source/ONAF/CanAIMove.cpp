// Fill out your copyright notice in the Description page of Project Settings.


#include "CanAIMove.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UCanAIMove::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	if(OwnerComp.GetBlackboardComponent())
	{
		return OwnerComp.GetBlackboardComponent()->GetValueAsBool("CanMove");
	}

	UE_LOG(LogTemp, Error, TEXT("CanMove decorator failed!"))
	return false;
}


