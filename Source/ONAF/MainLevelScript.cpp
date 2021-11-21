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

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	check(Player);

	PlayerController = Cast<ASecurityGuardController>(Player->GetController());

	check(PlayerController);
	
	for (TActorIterator<ALevelSequenceActor> it(GetWorld()); it; ++it)
	{
		LevelSeqActor = *it;

		//if we found it, then break the game
		if (LevelSeqActor->GetName() == TEXT("LeftDoor")) break;
	}

	check(LevelSeqActor)
	
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
void AMainLevelScript::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(!bIsDoorOpen)
	{
		PlayerController->DecreasePower();
	}
	if(PlayerController->GetMusicBoxPercent() <= 0.f)
	{
		//Jumpscare if the music box percentage is 0
		PuppetJumpscare();
	}
	if(PlayerController->GetPower() <= 0.f)
	{
		CloseDoor();
	}
}


void AMainLevelScript::ActionsOnState()
{
	Player->SetCanRotate(false);
	switch(Player->GetCurrentState())
	{
		case EFront:
			Front();
			Player->SetCanRotate(true);
			break;
		case EBack:
			Back();
		if(!bIsInHallway) Player->SetCanRotate(true);
			break;
		case ERight:
			Right();
			Player->SetCanRotate(true);
			break;
		case ELeft:
			Left();
			Player->SetCanRotate(true);
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
void AMainLevelScript::CloseDoor()
{
	LevelSeqActor->SequencePlayer->PlayReverse();
	UGameplayStatics::PlaySound2D(GetWorld(), PowerGoneSound);
}
