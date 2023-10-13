// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	void PullTrigger();
	void PullTriggerZeroAmmo();

	UFUNCTION()
	void Reloading();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Stat")
	int MaxAmmo = 30;

	UPROPERTY(BlueprintReadOnly, Category = "Stat")
	int Ammo;
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* HitFlash;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* MuzzleSound;	
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* ImpactSound;	

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* OutOfAmmoSound;
	
	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxRange = 10000;
	
	UPROPERTY(EditAnywhere, Category = "Stat")
	float Damage = 10;
	
	
	bool GunTrace(FHitResult &HitResult, FVector &ShotDirection) const;
	AController* GetOwnerController() const;
};
