// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevelScript.h"
#include "EngineUtils.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequenceActor.h"
#include "SecurityGuardController.h"
#include "Cameras.h"



void AMainLevelScript::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	check(Player);

	PlayerController = Cast<ASecurityGuardController>(Player->GetController());

	check(PlayerController);

	//Getting camera widget
	UCameras* Cameras = PlayerController->CreateCameraWidget();
	check(Cameras)
	Cameras->OnPartyRoom1Clicked.AddDynamic(this, &AMainLevelScript::SwitchToPartyRoom1Cam);
	Cameras->OnPartyRoom2Clicked.AddDynamic(this, &AMainLevelScript::SwitchToPartyRoom2Cam);
	Cameras->OnHallway1CamClicked.AddDynamic(this, &AMainLevelScript::SwitchToHallway1Cam);
	Cameras->OnHallway2CamClicked.AddDynamic(this, &AMainLevelScript::SwitchToHallway2Cam);
	Cameras->OnExitBtnClicked.AddDynamic(this, &AMainLevelScript::ExitFromCamSystem);

	FirstCamera = PlayerController->GetViewTarget();
	
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
	//Later I will add some functionality to it
}

void AMainLevelScript::Back()
{
	//If player is already in hallway, then run from the hallway
	if (bIsInHallway)
	{
		Player->RunFromHallway();
		PlayerController->SetIsAtMusicBox(false);
	}
	//Else run to the hallway
	else
	{
		Player->RunToHallway();
		PlayerController->SetIsAtMusicBox(true);
	}
	bIsInHallway = !bIsInHallway;
}

void AMainLevelScript::Right()
{
	PlayerController->SwitchWidgetVisibility();
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

void AMainLevelScript::SwitchToPartyRoom1Cam()
{
	PlayerController->SetViewTarget(PartyRoom1Cam);
	PlayerController->SwitchWidgetVisibility();
}

void AMainLevelScript::SwitchToPartyRoom2Cam()
{
	PlayerController->SetViewTarget(PartyRoom2Cam);
	PlayerController->SwitchWidgetVisibility();
	
}

void AMainLevelScript::SwitchToHallway1Cam()
{
	PlayerController->SetViewTarget(Hallway1Cam);
	PlayerController->SwitchWidgetVisibility();
}

void AMainLevelScript::SwitchToHallway2Cam()
{
	PlayerController->SetViewTarget(Hallway2Cam);
	PlayerController->SwitchWidgetVisibility();
}

void AMainLevelScript::ExitFromCamSystem()
{
	PlayerController->SwitchWidgetVisibility();
	PlayerController->SetViewTarget(FirstCamera);
}
