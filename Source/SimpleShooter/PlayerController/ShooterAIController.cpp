// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "../Actor/ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLoaction"), GetPawn()->GetActorLocation());
	}
}

// 적군 AI가 날 확인하였을시 음성 재생

void AShooterAIController::DetectEnemy() const
{
	const APawn* MyPawn = GetPawn();
	if (MyPawn != nullptr)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), EnemyDetectSoundClass, MyPawn->GetActorLocation(), MyPawn->GetActorRotation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
	const AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}
