// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityGuardController.h"
#include "Blueprint/UserWidget.h"

void ASecurityGuardController::CreateWidgetBasedOnBool()
{
	//If camera widget is already spawned, then deleting it and giving a null value
	if(CameraWidget)
	{
		CameraWidget->RemoveFromParent();
		CameraWidget = nullptr;
		
	}
	//Else spawning camera widget normally
	else
	{
		if(IsValid(WidgetToSpawn))
		{
			CameraWidget = CreateWidget<UUserWidget>(this, WidgetToSpawn, TEXT("CameraWidget"));
			if(CameraWidget) CameraWidget->AddToViewport();
			else UE_LOG(LogTemp, Error, TEXT("Error at spawning widget"))
		}
	}
}
