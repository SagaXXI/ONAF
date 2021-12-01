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

	//Class used to open and close the door
	class ALevelSequenceActor* LevelSeqActor = nullptr;

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

	//Used to control the jumpscare appearence
	bool NeedToJumpscare = true;
public:

	class APlayerCharacter* Player;

	class ASecurityGuardController* PlayerController;
protected:
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

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

	//Function used to call when the power is gone (basically, just closing the door and playing sound
	void CloseDoor();

	//Sound which will be called when the power is gone
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (BlueprintProtected = true))
	USoundBase* PowerGoneSound;

	//Puppet jumpscare
	UFUNCTION(BlueprintImplementableEvent, Category = "MusicBox")
	void PuppetJumpscare();


	
};
