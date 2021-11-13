// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SecurityGuardController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicBoxPercentChange, float, Percent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, int32, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPowerPercentChange, float, Percent);

UCLASS()
class ONAF_API ASecurityGuardController : public APlayerController
{
	GENERATED_BODY()

	class UCameras* CameraWidget = nullptr;

	//Variable to control whether player is at the music box or not
	bool bIsAtMusicBox = false;

	//Current time in game
	int32 CurrentTime = 12;
	
public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	UCameras* CreateCameraWidget();

	UFUNCTION(BlueprintPure, Category = "UI") FORCEINLINE
	UCameras* GetCameraWidget() { return CameraWidget;}
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SwitchWidgetVisibility();
	
	UFUNCTION(Category = "MusicBox") 
	void SetIsAtMusicBox(bool NewState);

	UFUNCTION(BlueprintPure, Category = "MusicBox") FORCEINLINE
	float GetMusicBoxPercent() { return MusicBoxPercent; }

	FOnMusicBoxPercentChange OnMusicBoxPercentChange;

	FOnTimeChanged OnTimeChanged;

	FOnPowerPercentChange OnPowerPercentChange;

	//Game win or over stuff
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameOver", meta = (BlueprintProtected = true))
	TSubclassOf<class UUserWidget> GameOverWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameOver", meta = (BlueprintProtected = true))
	TSubclassOf<class UUserWidget> GameWinWidget;

	UFUNCTION(BlueprintCallable, Category = "GameOver")
	void SetbIsGameOver(bool NewState);

	//Power stuff
	UFUNCTION(BlueprintPure, Category = "Power") FORCEINLINE
	float GetPower() {return Power;}

	UFUNCTION(BlueprintCallable, Category = "Power")
	void DecreasePower();
	
	
	
protected:

	void Tick(float DeltaSeconds) override;
	
	virtual void BeginPlay() override;
	//Controlling the camera system and spawning camera widget
	// The class that will be used to Spawn a widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (BlueprintProtected = true))
	TSubclassOf<class UCameras> WidgetToSpawn;

	//Music box stuff
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MusicBox")
	float MusicBoxPercent = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MusicBox", meta = (BlueprintProtected = true))
	float MusicBoxPercentIncrement = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MusicBox", meta = (BlueprintProtected = true))
	float MusicBoxPercentDecrement = 0.005f;

	UFUNCTION(BlueprintCallable, Category = "MusicBox")
	void MusicBoxProgressChange();

	//Time tracking stuff
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time", meta = (BlueprintProtected = true))
	float OneHourDurationInSec = 60.f;

	FTimerHandle HourPassedHandle;
	
	void TimeTracking();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time", meta = (BlueprintProtected = true))
	USoundBase* VictorySound;

	//Power stuff
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power", meta = (BlueprintProtected = true))
	float Power = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power", meta = (BlueprintProtected = true))
	float PowerDecrement = 0.00015f;

	//Game win or over control stuff
	
	//Called on different game states
	void GameWin();

	void GameOver();
	
	bool bIsGameOver = false;
};
