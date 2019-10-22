// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Move.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Sheep/SheepAI.h"
#include "Sheep/SheepCharacter.h"
#include "Player/Char_Wolf.h"

EBTNodeResult::Type UBTTask_Move::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ASheepAI *SheepPC = Cast<ASheepAI>(OwnerComp.GetOwner());

	AChar_Wolf *Wolf = Cast<AChar_Wolf>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(SheepPC->WolfKeyID));

	if (Wolf)
	{
		SheepPC->MoveToActor(Wolf, 5.f, true, true, true, 0, true);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
