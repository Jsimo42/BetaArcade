// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RunAway.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Sheep/SheepAI.h"
#include "Sheep/SheepCharacter.h"
#include "Player/Char_Wolf.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Engine.h"

EBTNodeResult::Type UBTTask_RunAway::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ASheepAI *SheepPC = Cast<ASheepAI>(OwnerComp.GetOwner());

	AChar_Wolf *Wolf = Cast<AChar_Wolf>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(SheepPC->WolfKeyID));

	if (Wolf)
	{
		if (FVector::Dist(SheepPC->GetPawn()->GetActorLocation(), Wolf->GetActorLocation()) <= 300.f)
		{
			FVector movement = SheepPC->GetPawn()->GetActorLocation() - Wolf->GetActorLocation();
			movement.Normalize(1.f);

			movement = movement * 150;

			FVector dest = SheepPC->GetPawn()->GetActorLocation() + movement;

			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("working , vector to move = %f %f %f"), dest.X, dest.Y, dest.Z));

			SheepPC->MoveToLocation(dest, 5.f, true, true, true, true, 0, true);

			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	return EBTNodeResult::Failed;
}
