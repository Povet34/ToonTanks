// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

bool ATower::InFireRange()
{
    if(Tank)
    {
        float Dist = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Dist <= FireRange)
        {
            return true;
        }
    }
    return false;
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(InFireRange())
        RotateTurret(Tank->GetActorLocation());
}
    

void ATower::CheckFireCondition()
{

    if (Tank == nullptr)
    {
        return;
    }

    if(InFireRange() && Tank->bAlive) 
         Fire();
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); 
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}
