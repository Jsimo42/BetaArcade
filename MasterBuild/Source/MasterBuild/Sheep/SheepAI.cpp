// Fill out your copyright notice in the Description page of Project Settings.

#include "Sheep/SheepAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Sheep/SheepCharacter.h"

ASheepAI::ASheepAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
}


void ASheepAI::Possess(APawn *InPawn)
{
	Super::Possess(InPawn);

	ASheepCharacter *Char = Cast<ASheepCharacter>(InPawn);

	if (Char && Char->BotBehaviour)
	{
		BlackboardComp->InitializeBlackboard(*Char->BotBehaviour->BlackboardAsset);

		WolfKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp->StartTree(*Char->BotBehaviour);
	}
}