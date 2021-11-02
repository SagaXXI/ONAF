// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SecurityGuardController.generated.h"

/**
 * 
 */
UCLASS()
class ONAF_API ASecurityGuardController : public APlayerController
{
	GENERATED_BODY()

	class UUserWidget* CameraWidget = nullptr;
	
public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateWidgetBasedOnBool();

protected:
	//Controlling the camera system and spawning camera widget
	// The class that will be used to Spawn a widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (BlueprintProtected = true))
	TSubclassOf<class UUserWidget> WidgetToSpawn;
};
