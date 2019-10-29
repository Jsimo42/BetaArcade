// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PickUps/PickUpBase.h"
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
	UFUNCTION(BlueprintCallable)
		void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties")
		float moveSpeedMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties")
		int Points = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties")
		bool isSneaking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickups")
		APickUpBase* CurrentItem = NULL;

private:
	UFUNCTION(BlueprintCallable)
		void SetupOverlapEvents();


	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnRate(float Value);
	
	void Sneak();
	void StopSneaking();
	void Attack();

};
