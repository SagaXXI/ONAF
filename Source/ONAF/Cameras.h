// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cameras.generated.h"

//Button clicked events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPartyRoom1Clicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPartyRoom2Clicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHallway1CamClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHallway2CamClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitBtnClicked);

class UButton;
UCLASS()
class ONAF_API UCameras : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	//Beginplay analog for widgets
	void NativeConstruct() override;
	
	//Camera control
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UButton* PartyRoomCam1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* PartyRoomCam2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Hallway1Cam;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Hallway2Cam;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitBtn;

	//Functions to handle the buttons
	UFUNCTION()
	void PartyRoomCam1Clicked();

	UFUNCTION()
	void PartyRoomCam2Clicked();

	UFUNCTION()
	void Hallway1CamClicked();

	UFUNCTION()
	void Hallway2CamClicked();

	UFUNCTION()
	void ExitBtnClicked();

	//Delegates for the functions
public:
	FOnPartyRoom1Clicked OnPartyRoom1Clicked;
	FOnPartyRoom2Clicked OnPartyRoom2Clicked;
	FOnHallway1CamClicked OnHallway1CamClicked;
	FOnHallway2CamClicked OnHallway2CamClicked;
	FOnExitBtnClicked OnExitBtnClicked;
    	
};
