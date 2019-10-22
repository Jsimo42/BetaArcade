// Fill out your copyright notice in the Description page of Project Settings.

#include "SheepAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Sheep/SheepCharacter.h"

ASheepAI::ASheepAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}


void ASheepAI::Possess(APawn *InPawn)
{
	Super::Possess(InPawn);

	ASheepCharacter *sheep = Cast<ASheepCharacter>(InPawn);

	if (sheep && sheep->BotBehavior)
	{
		BlackboardComp->InitializeBlackboard(*sheep->BotBehavior->BlackboardAsset);

		WolfKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp->StartTree(*sheep->BotBehavior);
	}
}