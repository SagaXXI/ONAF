// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAroundRandomly.h"
#include "AnimatronicsController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


UMoveAroundRandomly::UMoveAroundRandomly()
{
	NodeName = "GetRandomReachablePoint";
}

EBTNodeResult::Type UMoveAroundRandomly::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Getting AIController
	AAnimatronicsController* AIController = Cast<AAnimatronicsController>(OwnerComp.GetAIOwner());

	//Getting the blackboard comp
	UBlackboardComponent* BBComp = AIController->GetBBComp();
	
	if(AIController && BBComp)
	{		
		
			//We need this struct to pass into the RandomReachable function to get a result of the location
			FVector Result;

			UNavigationSystemV1* NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
			if (NavArea)
			{
				Result = NavArea->GetRandomReachablePointInRadius(this, AIController->GetPawn()->GetActorLocation(),
				AIController->MovementRadius);
			}
			//Finally, setting blackboard variable to move to the location
			BBComp->SetValueAsVector("LocationToGo", Result);

			return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
