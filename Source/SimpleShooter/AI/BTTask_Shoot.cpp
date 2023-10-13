// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "../Actor/ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if(OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	AIController = OwnerComp.GetAIOwner();

	AShooterCharacter *AIPawn = Cast<AShooterCharacter>(AIController->GetPawn());
	if(AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if(AIPawn->GetAmmo() > 0)
	{
		AIPawn->Shot();
	}
	else
	{
		AIPawn->Reloading();
	}
	
	return EBTNodeResult::Succeeded;
}
