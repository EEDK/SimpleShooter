// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "../PlayerController/ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const AShooterAIController *AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	
	if(AIController == nullptr) return;
	
	APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(PlayerPawn == nullptr) return;
	
	if(AIController->LineOfSightTo(PlayerPawn))
	{
		if(OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("HasTarget")) == false)
			AIController->DetectEnemy();
		
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("HasTarget"), true);
	}
	
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("HasTarget"), false);
	}
}
