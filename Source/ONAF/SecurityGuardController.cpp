// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityGuardController.h"
#include "Blueprint/UserWidget.h"
#include "Cameras.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

//TODO fix the puppet jumpscare(mb implement her mechanics in bt and bb)
//make player turn towards freddy when freddy kills him
//Maybe (maybe) move everything(blueprint decorators and all that stuff) to cpp

void ASecurityGuardController::BeginPlay()
{
	Super::BeginPlay();
	
	//Starting tracking time
	GetWorldTimerManager().SetTimer(HourPassedHandle, this, &ASecurityGuardController::TimeTracking, OneHourDurationInSec, true);
}

UCameras* ASecurityGuardController::CreateCameraWidget()
{
	//Spawning the widget and hiding it
	if(IsValid(WidgetToSpawn))
	{
		CameraWidget = CreateWidget<UCameras>(this, WidgetToSpawn, TEXT("CameraWidget"));
		if(CameraWidget)
		{
			CameraWidget->AddToViewport();
			CameraWidget->SetVisibility(ESlateVisibility::Hidden);
			return CameraWidget;
		}		
	}
	//If we couldn't spawn it, then throwing an error
	UE_LOG(LogTemp, Error, TEXT("Error at spawning widget"))
	return nullptr;

}


void ASecurityGuardController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//This func is used to control the change of the percentage of music box and to broadcast the event 
	MusicBoxProgressChange();
	
}


void ASecurityGuardController::MusicBoxProgressChange()
{
	if(bIsAtMusicBox)
	{
		MusicBoxPercent += MusicBoxPercentIncrement;
		if(MusicBoxPercent > 1.f)
		{
			MusicBoxPercent = 1.f;
		}
	}
	else
	{
		MusicBoxPercent -= MusicBoxPercentDecrement;

		if(MusicBoxPercent == 0.f)
		{
		}
	}
	OnMusicBoxPercentChange.Broadcast(MusicBoxPercent);
}


void ASecurityGuardController::TimeTracking()
{
	if(!bIsGameOver)
	{
		if(CurrentTime == 12)
		{
			CurrentTime = 1;
		}
		else
		{
			if(CurrentTime == 5)
			{
				GameWin();
			}
			CurrentTime++;
		}
		OnTimeChanged.Broadcast(CurrentTime);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(HourPassedHandle);
	}
	
	
}

void ASecurityGuardController::GameWin()
{
	UGameplayStatics::PlaySound2D(GetWorld(), VictorySound);
	CameraWidget->RemoveFromParent();
	UUserWidget* GameWin = CreateWidget<UUserWidget>(this, GameWinWidget, TEXT("GameOver"));
	if(GameWin)
	{
		GameWin->AddToViewport();
		//Setting input mode only UI
		/*UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
			this, GameWin);*/
		SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnly(this, GameWin);
	}	
}

void ASecurityGuardController::GameOver()
{
	bIsGameOver = true;
	CameraWidget->RemoveFromParent();
	UUserWidget* GameOver = CreateWidget<UUserWidget>(this, GameOverWidget, TEXT("GameOver"));
	if(GameOver)
	{
		GameOver->AddToViewport();
		/*UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
		this, GameOver);*/
		SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnly(this, GameOver);
	}
}

void ASecurityGuardController::SwitchWidgetVisibility()
{
	//If camera widget is already spawned, then hiding it
	if(CameraWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		bIsCameraWidgetVisible = false;
		CameraWidget->SetVisibility(ESlateVisibility::Hidden);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
		SetShowMouseCursor(false);
	}
	//Else spawning camera widget normally
	else
	{
		bIsCameraWidgetVisible = true;
		CameraWidget->SetVisibility(ESlateVisibility::Visible);
		
		//Setting input mode only UI
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
			this, CameraWidget);
		
		SetShowMouseCursor(true);
	}
}


void ASecurityGuardController::DecreasePower()
{
	Power -= PowerDecrement;
	OnPowerPercentChange.Broadcast(Power);
}

void ASecurityGuardController::SetIsAtMusicBox(bool NewState)
{
	bIsAtMusicBox = NewState;
}

void ASecurityGuardController::SetbIsGameOver(bool NewState)
{
	bIsGameOver = NewState;
}
