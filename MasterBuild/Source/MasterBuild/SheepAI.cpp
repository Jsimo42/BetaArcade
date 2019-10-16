// Fill out your copyright notice in the Description page of Project Settings.

#include "SheepAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "SheepCharacter.h"


ASheepAI::ASheepAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	BehaviourComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
}

void ASheepAI::Possess(APawn *InPawn)
{
	Super::Possess(InPawn);

	ASheepCharacter *character = Cast<ASheepCharacter>(InPawn);

	/*if (character && character->)
	{
		BlackboardComp->InitializeBlackboard(*character->BotBehavior)
	}*/
}

