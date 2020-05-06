// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	if (!Trigger)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%s has no trigger volume attached!"), *this->GetName());
	}

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();	

	OriginalHeight = this->GetActorLocation().Z;
	OriginalX = this->GetActorLocation().X;
	OriginalY = this->GetActorLocation().Y;

	Height += OriginalHeight;
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Trigger)
	{
		return;
	}

	if (Trigger->IsOverlappingActor(Player))
	{
		MoveUp(DeltaTime);
	}
	else
	{
		MoveDown(DeltaTime);
	}
}

void AElevator::MoveUp(float DeltaTime)
{
	CurrentHeight = this->GetActorLocation().Z;

	this->SetActorLocation(FVector(OriginalX, OriginalY, FMath::FInterpConstantTo(CurrentHeight, Height, DeltaTime, MoveSpeed)));
}

void AElevator::MoveDown(float DeltaTime)
{
	CurrentHeight = this->GetActorLocation().Z;

	this->SetActorLocation(FVector(OriginalX, OriginalY, FMath::FInterpConstantTo(CurrentHeight, OriginalHeight, DeltaTime, MoveSpeed)));
}