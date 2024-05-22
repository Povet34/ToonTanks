// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

ATank::ATank(){
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::Move(float Value){

    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Trun(float Value){
    
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value * RotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
    PlayerControllerRef = Cast<APlayerController>(GetController());
}
 
void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent){
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Trun);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    FHitResult hitResult;
    bool HasHit = PlayerControllerRef->GetHitResultUnderCursor(
        ECC_Visibility,
        false,
        hitResult
    );

    if(HasHit){
        DrawDebugSphere(
            GetWorld(), 
            hitResult.ImpactPoint, 
            50.f, 10,
            FColor::Red, false, -1.f
        );

        RotateTurret(hitResult.ImpactPoint);
    }
}
