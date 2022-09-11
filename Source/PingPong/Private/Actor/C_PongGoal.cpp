// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/C_PongGoal.h"

// Sets default values
AC_PongGoal::AC_PongGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PongGoalMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PongGoalMesh"));
	PongGoalMeshComponent->SetCollisionProfileName("BlockAll");
	RootComponent = PongGoalMeshComponent;
}

// Called when the game starts or when spawned
void AC_PongGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PongGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

