	// Fill out your copyright notice in the Description page of Project Settings.


	#include "PlayerCharacter.h"
	#include "Components/CapsuleComponent.h"

	// Sets default values
	APlayerCharacter::APlayerCharacter()
	{
 		// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

		/*CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Capsule"));
		RootComponent = CollisionCapsule;

		Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
		Mesh->SetupAttachment(RootComponent);*/
		
		// Create a follow camera
		Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(GetMesh(), FName("headSocket")); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation

	}

	//////////////////////////////////////////////////////////////////////////
	// Input

	void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
	{
		// Set up gameplay key bindings
		check(PlayerInputComponent);
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	}

	// Called every frame
	void APlayerCharacter::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

	}
	// Called when the game starts or when spawned
	void APlayerCharacter::BeginPlay()
	{
		Super::BeginPlay();
		
	}



