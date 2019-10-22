// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SheepAI.generated.h"

/**
 * 
 */
UCLASS()
class MASTERBUILD_API ASheepAI : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(transient)
	class UBlackboardComponent *BlackboardComp;

	UPROPERTY(transient)
	class UBehaviorTreeComponent *BehaviorComp;

public:
	ASheepAI();
	
	virtual void Possess(APawn *InPawn) override;
	
	uint8 WolfKeyID;
};
