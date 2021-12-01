// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAnimatronic.h"
#include "AnimatronicsController.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAIAnimatronic::AAIAnimatronic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
}

// Called when the game starts or when spawned
void AAIAnimatronic::BeginPlay()
{
	Super::BeginPlay();

	if(PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AAIAnimatronic::OnPlayerCaught);
	}

	GetCharacterMovement()->MaxWalkSpeed = 110.f;
	
}

void AAIAnimatronic::OnPlayerCaught(APawn* Pawn)
{
	AAnimatronicsController* AIController = Cast<AAnimatronicsController>(GetController());

	//Check if player
	APlayerCharacter* Player = Cast<APlayerCharacter>(Pawn);
	if(Player && AIController)
	{
		AIController->SetPlayerCaught(Pawn->GetActorLocation());
	}

}


