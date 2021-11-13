// Fill out your copyright notice in the Description page of Project Settings.


#include "Cameras.h"
#include "SecurityGuardController.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UCameras::NativeConstruct()
{
	Super::NativeConstruct();
	//Binding the functions to actual widgets
	if(PartyRoomCam1)
	{
		PartyRoomCam1->OnClicked.AddDynamic(this, &UCameras::PartyRoomCam1Clicked);
	}
	if(PartyRoomCam2)
	{
		PartyRoomCam2->OnClicked.AddDynamic(this, &UCameras::PartyRoomCam2Clicked);
	}
	if(Hallway1Cam)
	{
		Hallway1Cam->OnClicked.AddDynamic(this, &UCameras::Hallway1CamClicked);
	}
	if(Hallway2Cam)
	{
		Hallway2Cam->OnClicked.AddDynamic(this, &UCameras::Hallway2CamClicked);
	}
	if(ExitBtn)
	{
		ExitBtn->OnClicked.AddDynamic(this, &UCameras::ExitBtnClicked);
	}

	ASecurityGuardController* PlayerController = Cast<ASecurityGuardController>(GetOwningPlayer());
	check(PlayerController)
	
	if(MusicBoxProgress)
	{
		PlayerController->OnMusicBoxPercentChange.AddDynamic(this, &UCameras::SetMusicBoxPercent);
	}

	if(Time)
	{
		Time->SetText(FText::AsNumber(12));
		PlayerController->OnTimeChanged.AddDynamic(this, &UCameras::SetNewTime);
	}

	if(PowerProgress)
	{
		PlayerController->OnPowerPercentChange.AddDynamic(this, &UCameras::SetPowerPercent);
	}
}

void UCameras::PartyRoomCam1Clicked()
{
	OnPartyRoom1Clicked.Broadcast();
}

void UCameras::PartyRoomCam2Clicked()
{
	OnPartyRoom2Clicked.Broadcast();
}

void UCameras::Hallway1CamClicked()
{
	OnHallway1CamClicked.Broadcast();
}

void UCameras::Hallway2CamClicked()
{
	OnHallway2CamClicked.Broadcast();
}

void UCameras::ExitBtnClicked()
{
	OnExitBtnClicked.Broadcast();
}

void UCameras::SetMusicBoxPercent(float NewPercent)
{
	MusicBoxProgress->SetPercent(NewPercent);
}

void UCameras::SetPowerPercent(float NewPercent)
{
	PowerProgress->SetPercent(NewPercent);
}

void UCameras::SetNewTime(int32 NewTime)
{
	Time->SetText(FText::AsNumber(NewTime));
}
