// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevelScript.generated.h"

class ULevelSequencePlayer;
class ULevelSequence;

UCLASS()
class ONAF_API AMainLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Switch")
	void ActionsOnState();

	//Handling different states
	void Front();
	
	//Opening left door
	void Left();
	
	//Running to the hallway door and opening/closing it
	void Back();

	//View cameras
	void Right();

	//Bool which will control bool flow (Flip flop) (On door opening/closing)
	bool bIsDoorOpen = true;

	//Bool which will control bool flow (Flip flop) (On running to the hallway and running from the hallway)
	bool bIsInHallway = false;

	//Camera switching control functions

	UFUNCTION()
	void SwitchToPartyRoom1Cam();
	
	UFUNCTION()
	void SwitchToPartyRoom2Cam();

	UFUNCTION()
	void SwitchToHallway1Cam();

	UFUNCTION()
	void SwitchToHallway2Cam();

	UFUNCTION()
	void ExitFromCamSystem();

	//First (Player's real) Camera
	AActor* FirstCamera = nullptr;
public:

	class APlayerCharacter* Player;

	class ASecurityGuardController* PlayerController;
protected:
	void BeginPlay() override;

	// Sequence Assets
	UPROPERTY()
	ULevelSequencePlayer* SequencePlayer;
 
	UPROPERTY(EditAnywhere, Category = "LevelSeq", meta = (BlueprintProtected = true))
	ULevelSequence* SequenceAsset;

	UPROPERTY(EditAnywhere, Category = "FX")
	USoundBase* DoorSound;

	//Camera references
	UPROPERTY(EditAnywhere, Category = "Cameras")
	AActor* PartyRoom1Cam;

	UPROPERTY(EditAnywhere, Category = "Cameras")
	AActor* PartyRoom2Cam;

	UPROPERTY(EditAnywhere, Category = "Cameras")
	AActor* Hallway1Cam;

	UPROPERTY(EditAnywhere, Category = "Cameras")
	AActor* Hallway2Cam;

	
};
