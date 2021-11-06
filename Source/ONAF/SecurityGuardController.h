// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SecurityGuardController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMusicBoxPercentChange, float, Percent);

UCLASS()
class ONAF_API ASecurityGuardController : public APlayerController
{
	GENERATED_BODY()

	class UCameras* CameraWidget = nullptr;

	//Variable to control whether player is at the music box or not
	bool bIsAtMusicBox = false;
	
public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	UCameras* CreateCameraWidget();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SwitchWidgetVisibility();
	
	FORCEINLINE UFUNCTION(Category = "MusicBox") 
	void SetIsAtMusicBox(bool NewState) {bIsAtMusicBox = NewState; }

	UFUNCTION(BlueprintPure, Category = "MusicBox") FORCEINLINE
	float GetMusicBoxPercent() { return MusicBoxPercent; }

	FOnMusicBoxPercentChange OnMusicBoxPercentChange;

protected:
	//Controlling the camera system and spawning camera widget
	// The class that will be used to Spawn a widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (BlueprintProtected = true))
	TSubclassOf<class UCameras> WidgetToSpawn;

	void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MusicBox")
	float MusicBoxPercent = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MusicBox", meta = (BlueprintProtected = true))
	float MusicBoxPercentIncrement = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MusicBox", meta = (BlueprintProtected = true))
	float MusicBoxPercentDecrement = 0.005f;

};
