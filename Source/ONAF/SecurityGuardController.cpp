// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityGuardController.h"
#include "Blueprint/UserWidget.h"
#include "Cameras.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


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
	if(bIsAtMusicBox)
	{
		MusicBoxPercent += MusicBoxPercentIncrement;
		if(MusicBoxPercent > 1.f)
		{
			MusicBoxPercent = 1.f;
		}

		OnMusicBoxPercentChange.Broadcast(MusicBoxPercent);
	}
	else
	{
		MusicBoxPercent -= MusicBoxPercentDecrement;
		OnMusicBoxPercentChange.Broadcast(MusicBoxPercent);
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

