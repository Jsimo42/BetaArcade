// Fill out your copyright notice in the Description page of Project Settings.

#include "Char_Wolf.h"


// Sets default values
AChar_Wolf::AChar_Wolf()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChar_Wolf::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AChar_Wolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChar_Wolf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Sneak", IE_Pressed, this, &AChar_Wolf::Sneak);
	PlayerInputComponent->BindAction("Sneak", IE_Released, this, &AChar_Wolf::StopSneaking);

	PlayerInputComponent->BindAxis("MoveForward", this, &AChar_Wolf::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AChar_Wolf::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AChar_Wolf::TurnRate);
}

void AChar_Wolf::MoveForward(float Value)
{

	{
		moveSpeedMultiplier = 0.3f;
	}

	Value = Value * moveSpeedMultiplier;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AChar_Wolf::MoveRight(float Value)
{
	if (isSneaking == true)
	{
		moveSpeedMultiplier = 0.3f;
	}

	Value = Value * moveSpeedMultiplier;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value); 
	}
}

void AChar_Wolf::TurnRate(float Rate)
{
	AddControllerYawInput(Rate * 45 * GetWorld()->GetDeltaSeconds());
}

void AChar_Wolf::Sneak()
{
	isSneaking = true;

	moveSpeedMultiplier = 0.3f;
}

void AChar_Wolf::StopSneaking()
{
	isSneaking = false;

	moveSpeedMultiplier = 1.0f;
}


