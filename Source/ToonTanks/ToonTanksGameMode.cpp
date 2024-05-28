// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Tower.h"
#include "TimerManager.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    UE_LOG(LogTemp, Display, TEXT("%s"), *DeadActor->GetName());

    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        --TargetTowers;
        if(TargetTowers <= 0)
        {
            GameOver(true);
        }
    }

    FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(this, &AToonTanksGameMode::BeginPlay);
}

 void AToonTanksGameMode::HandleGameStart()
 {
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        );

        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
    }
 }

 void AToonTanksGameMode::BeginPlay()
 {
    HandleGameStart();
 }

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}