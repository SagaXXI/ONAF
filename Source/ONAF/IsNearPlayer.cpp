// Fill out your copyright notice in the Description page of Project Settings.


#include "IsNearPlayer.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

bool UIsNearPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);

	if(PlayerPawn && OwnerComp.GetAIOwner())
	{
		//Distance between AI and player
		float Distance = FVector::Dist(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
		if(Distance <= 100.f)
		{
			return true;
		}
	}

	return false;
}
