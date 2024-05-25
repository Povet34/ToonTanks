// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    UE_LOG(LogTemp, Display, TEXT("%s"), *DeadActor->GetName());

    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(Tank->GetTankPlayerController())
        {
            Tank->DisableInput(Tank->GetTankPlayerController());
            Tank->GetTankPlayerController()->bShowMouseCursor = false;
        }
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
    }
}

 void AToonTanksGameMode::BeginPlay()
 {
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
 }