// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AGamePlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	if(Hud != nullptr)
	{
		Hud->RemoveFromViewport();
	}

	if(bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if(WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if(LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	Hud = CreateWidget(this, HudClass);

	if(Hud != nullptr)
	{
		Hud->AddToViewport();
	}
}
