// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckForPlayer.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Sheep/SheepAI.h"
#include "Sheep/SheepCharacter.h"
#include "Player/Char_Wolf.h"

UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeonds)
{
	ASheepAI *SheepPC = Cast<ASheepAI>(OwnerComp.GetAIOwner());

	if (SheepPC)
	{
		AChar_Wolf *Wolf = Cast<AChar_Wolf>(GetWorld()->GetFirstPlayerController()->GetPawn());

		float distance = FVector::Dist(SheepPC->GetPawn()->GetActorLocation(), Wolf->GetActorLocation());

		TArray<AActor*> players;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChar_Wolf::StaticClass(), players);

		for (int i = 0; i < players.Num(); i++)
		{
			float testDist = FVector::Dist(SheepPC->GetPawn()->GetActorLocation(), Cast<AChar_Wolf>(players[i])->GetActorLocation());
			if (testDist < distance)
			{
				Wolf = Cast<AChar_Wolf>(players[i]);
				distance = testDist;
			}
		}

		if (Wolf)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(SheepPC->WolfKeyID, Wolf);
		}
	}
}