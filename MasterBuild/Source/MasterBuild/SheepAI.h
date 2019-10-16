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
	UBlackboardComponent *BlackboardComp;

	UPROPERTY(transient)
	UBehaviorTreeComponent *BehaviourComp;

public:
	ASheepAI();

	virtual void Possess(APawn *InPawn) override;

	uint8 SheepKeyID;

	
	
};
