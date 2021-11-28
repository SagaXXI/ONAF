// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimatronicsController.h"
#include "AIAnimatronic.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAnimatronicsController::AAnimatronicsController()
{
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComp"));
	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComp"));

	//Assigning names of the blackboard variables
	PlayerLocation = "PlayerLocation";
	StartLocation = "StartLocation";
	CanMove = "CanMove";
	LocationToGo = "LocationToGo";
	IsPlayerDead = "IsPlayerDead";
}

void AAnimatronicsController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Getting ref to animatronic
	AAIAnimatronic* Animatronic = Cast<AAIAnimatronic>(InPawn);

	//Setting all refs of BT and BB and starting the BT execution
	if(Animatronic && Animatronic->BehaviorTree)
	{
		//Passing by ref because the InitializeBlackboard need a ref not a pointer as a parameter
		BBComp->InitializeBlackboard(*Animatronic->BehaviorTree->BlackboardAsset);
		RunBehaviorTree(Animatronic->BehaviorTree);
		
	}

	if(BBComp)
	{
		BBComp->SetValueAsVector(StartLocation, InPawn->GetActorLocation());
		BBComp->SetValueAsBool(CanMove, true);
		BBComp->SetValueAsBool(IsPlayerDead, false);
	}
}


void AAnimatronicsController::SetPlayerCaught(FVector PawnLocation)
{
	if(BBComp)
	{
		BBComp->SetValueAsVector(PlayerLocation, PawnLocation);
		BBComp->SetValueAsBool(CanMove, false);
	}
	
}
