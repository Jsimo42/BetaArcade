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

	//SetupInputComponent();
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

}

void AChar_Wolf::SetupInputComponent()
{
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (inputComponent)
	{
		inputComponent->BindAction("MoveForward", IE_Pressed, this, &AChar_Wolf::MoveForward);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input Componenet"), *GetOwner()->GetName())
	}
}

void AChar_Wolf::MoveForward()
{
	//AddMovementInput({ 0,90,0 }, 1);
}

void AChar_Wolf::MoveBack()
{
}

void AChar_Wolf::MoveRight()
{
}

void AChar_Wolf::MoveLeft()
{
}

void AChar_Wolf::TurnRight()
{
}

void AChar_Wolf::TurnLeft()
{
}

