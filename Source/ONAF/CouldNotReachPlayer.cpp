// Fill out your copyright notice in the Description page of Project Settings.


#include "CouldNotReachPlayer.h"
#include "AnimatronicsController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


EBTNodeResult::Type UCouldNotReachPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAnimatronicsController* AIController = Cast<AAnimatronicsController>(OwnerComp.GetAIOwner());

	//Getting the blackboard comp
	UBlackboardComponent* BBComp = AIController->GetBBComp();
	
	if(AIController && BBComp)
	{
        ACharacter* AICharacter = Cast<ACharacter>(AIController->GetPawn());
        
        check(AICharacter)
        		
        AICharacter->GetCharacterMovement()->MaxWalkSpeed = 150.f;
		BBComp->ClearValue("LocationToGo");
        return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
