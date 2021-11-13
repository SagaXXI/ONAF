// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityGuardController.h"
#include "Blueprint/UserWidget.h"
#include "Cameras.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

//TODO create events when player dies and fix the mouse bug with the gameover and gamewin,
//fix the puppet jumpscare(mb implement her mechanics in bt and bb)

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
			/*CameraWidget->RemoveFromParent();
			UUserWidget* GameOver = CreateWidget<UUserWidget>(this, GameOverWidget, TEXT("GameOver"));
			if(GameOver)
			{
				GameOver->AddToViewport();
				UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
				this, GameOver);
				SetShowMouseCursor(true);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Music box has expired! Try again!"));
			}	*/
		}
	}
	OnMusicBoxPercentChange.Broadcast(MusicBoxPercent);
}


void ASecurityGuardController::TimeTracking()
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

void ASecurityGuardController::GameWin()
{
	UGameplayStatics::PlaySound2D(GetWorld(), VictorySound);
	CameraWidget->RemoveFromParent();
	UUserWidget* GameWin= CreateWidget<UUserWidget>(this, GameWinWidget, TEXT("GameOver"));
	if(GameWin)
	{
		GameWin->AddToViewport();
		//Setting input mode only UI
		/*UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
			this, GameWin);*/
		UWidgetBlueprintLibrary::SetInputMode_UIOnly(this, GameWin);
		
		SetShowMouseCursor(true);
	}	
}

void ASecurityGuardController::GameOver()
{
	CameraWidget->RemoveFromParent();
	UUserWidget* GameOver = CreateWidget<UUserWidget>(this, GameOverWidget, TEXT("GameOver"));
	if(GameOver)
	{
		GameOver->AddToViewport();
		/*UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
		this, GameOver);*/
		UWidgetBlueprintLibrary::SetInputMode_UIOnly(this, GameOver);
		SetShowMouseCursor(true);
	}
}

void ASecurityGuardController::SwitchWidgetVisibility()
{
	//If camera widget is already spawned, then deleting it and giving a null value
	if(CameraWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		CameraWidget->SetVisibility(ESlateVisibility::Hidden);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
		SetShowMouseCursor(false);
	}
	//Else spawning camera widget normally
	else
	{
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
