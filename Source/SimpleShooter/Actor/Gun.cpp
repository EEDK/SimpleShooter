// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	// 총구 화염 및 소리 Spawn
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	
	FHitResult HitResult;
	FVector ShotDirection;
	
	bool bSuccess= GunTrace(HitResult, ShotDirection);
	if(bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, HitResult.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, HitResult.Location,ShotDirection.Rotation());
		
		AActor* HitActor = HitResult.GetActor();
		
		if(HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			AController *OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

void AGun::PullTriggerZeroAmmo()
{
	UGameplayStatics::SpawnSoundAttached(OutOfAmmoSound, Mesh, TEXT("MuzzleFlashSocket"));
}

void AGun::Reloading()
{
	Ammo = MaxAmmo;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	Ammo = MaxAmmo;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection) const
{
	FVector Location;
	FRotator Rotation;
	const AController *OwnerController = GetOwnerController();
	if(OwnerController == nullptr) return false;
	
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	const FVector End = Location + Rotation.Vector() * MaxRange;
	ShotDirection = -Rotation.Vector();

	// 자기 자신에게 맞지 않도록 Collision Param값 전달
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	// Bullet이 적중된 곳에 HitFlash 생성
	return GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;
	
	return OwnerPawn->GetController();
}
