// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevelScript.h"
#include "EngineUtils.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequenceActor.h"
#include "SecurityGuardController.h"



void AMainLevelScript::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	check(Player);

	PlayerController = Cast<ASecurityGuardController>(Player->GetController());

	check(PlayerController);
}

void AMainLevelScript::ActionsOnState()
{
	switch(Player->GetCurrentState())
	{
		case EFront:
			Front();
			break;
		case EBack:
			Back();
			break;
		case ERight:
			Right();
			break;
		case ELeft:
			Left();
			break;
	default: ;
	}
	
}

void AMainLevelScript::Front()
{
	
}

void AMainLevelScript::Back()
{
	//If player is already in hallway, then run from the hallway
	if (bIsInHallway)
	{
		Player->RunFromHallway();
	}
	//Else run to the hallway
	else
	{
		Player->RunToHallway();
	}
	bIsInHallway = !bIsInHallway;
}

void AMainLevelScript::Right()
{
	PlayerController->CreateWidgetBasedOnBool();
}

void AMainLevelScript::Left()
{
	//Find the right level sequence actor in the world
	ALevelSequenceActor* LevelSeqActor = nullptr;
	for (TActorIterator<ALevelSequenceActor> it(GetWorld()); it; ++it)
	{
		LevelSeqActor = *it;

		//if we found it, then break the game
		if (LevelSeqActor->GetName() == TEXT("LeftDoor")) break;
	}

	if(LevelSeqActor)
	{
		if (bIsDoorOpen)
		{
			LevelSeqActor->SequencePlayer->Play();
			UGameplayStatics::PlaySound2D(GetWorld(), DoorSound, 1, 3);
		}
		else
		{
			LevelSeqActor->SequencePlayer->PlayReverse();
			UGameplayStatics::PlaySound2D(GetWorld(), DoorSound, 1, 3);
		}
		bIsDoorOpen = !bIsDoorOpen;
	}
}

