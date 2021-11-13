// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWasSeen.h"
#include "AnimatronicsController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UPlayerWasSeen::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAnimatronicsController* AIController = Cast<AAnimatronicsController>(OwnerComp.GetAIOwner());

	//Getting the blackboard comp
	UBlackboardComponent* BBComp = AIController->GetBBComp();
	
	if(AIController && BBComp)
	{
		//Setting the max walk speed
		ACharacter* AICharacter = Cast<ACharacter>(AIController->GetPawn());

		check(AICharacter)
		
		AICharacter->GetCharacterMovement()->MaxWalkSpeed = 500.f;
		BBComp->SetValueAsVector("LocationToGo", BBComp->GetValueAsVector("PlayerLocation"));

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


