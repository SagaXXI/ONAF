// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum  EPlayerRotState
{
	EFront,
	EBack,
	ELeft,
	ERight
};

UCLASS()
class ONAF_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, Category = "Actions") FORCEINLINE
	EPlayerRotState GetCurrentState() {return State;}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Comps")
	UCameraComponent* Camera;

	//Used to interact with the environment at different states
	//void Interact();

	UFUNCTION(BlueprintImplementableEvent, Category = "Actions")
	void DoorOpenCloseAnim();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actions", meta = (BlueprintProtected = true))
	TEnumAsByte <EPlayerRotState> State;
	

};
