// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "AIAnimatronic.generated.h"

UCLASS()
class ONAF_API AAIAnimatronic : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIAnimatronic();

	//BT reference
	UPROPERTY(EditDefaultsOnly, Category = "Comps")
	class UBehaviorTree* BehaviorTree;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Comps")
	UPawnSensingComponent* PawnSensing;

	//Function used to bind to OnSeePawn event
	UFUNCTION()
	void OnPlayerCaught(APawn* Pawn);


};
