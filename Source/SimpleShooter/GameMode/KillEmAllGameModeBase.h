// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameModeBase : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

public:
	AKillEmAllGameModeBase();
	virtual void PawnKilled(APawn* KilledPawn) override;

protected:
	virtual void BeginPlay() override;
	
private:
	void EndGame(bool bIsPlayerWinner);

	UPROPERTY(EditAnywhere, Category = "BGM")
	USoundBase *BackgroundMusic;
};
