// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/InputComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Char_Wolf.generated.h"

UCLASS()
class MASTERBUILD_API AChar_Wolf : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChar_Wolf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties")
		float moveSpeed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties")
		bool isSneaking = false;

private:

	UInputComponent* inputComponent = nullptr;

	void SetupInputComponent();

	void MoveForward();
	void MoveBack();
	void MoveRight();
	void MoveLeft();

	void TurnRight();
	void TurnLeft();
};
