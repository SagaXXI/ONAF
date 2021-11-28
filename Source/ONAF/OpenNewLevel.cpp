// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenNewLevel.h"
#include "Kismet/GameplayStatics.h"
#include "Cameras.h"
#include "SecurityGuardController.h"

EBTNodeResult::Type UOpenNewLevel::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("asdfjas"));
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	ASecurityGuardController* PlayerController = Cast<ASecurityGuardController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if(PlayerController)
	{
		
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		PlayerController->GameOver();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;

	
}
