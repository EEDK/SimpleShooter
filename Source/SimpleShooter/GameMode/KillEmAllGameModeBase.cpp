// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "../PlayerController/ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

AKillEmAllGameModeBase::AKillEmAllGameModeBase()
{

}

void AKillEmAllGameModeBase::PawnKilled(APawn* KilledPawn)
{
	Super::PawnKilled(KilledPawn);

	APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());

	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	for (const AShooterAIController* AIShooterController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if(!AIShooterController->IsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AKillEmAllGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->ConsoleCommand("DISABLEALLSCREENMESSAGES");
	}

	if (BackgroundMusic)
	{
		UGameplayStatics::PlaySound2D(this, BackgroundMusic);
	}
}


void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		const bool bIsPlayer = Controller->IsPlayerController();
		// 플레이어 일시 IsPlayerWinner의 값을 전달, AI일시 반대값을 전달
		// Ex) 플레이어 승리 플레이어 -> true, AI -> false
		bIsPlayer
			? Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerWinner)
			: Controller->GameHasEnded(Controller->GetPawn(), !bIsPlayerWinner);
	}
}
