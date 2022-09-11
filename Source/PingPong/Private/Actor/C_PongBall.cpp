// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/C_PongBall.h"
#include "Components/BoxComponent.h"
#include "Actor/C_PongWall.h"
#include "Actor/C_PongGoal.h"
#include "Core/Paddle.h"

// Sets default values
AC_PongBall::AC_PongBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PongBallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PongBallMesh"));
	PongBallMeshComponent->SetSimulatePhysics(true);
	PongBallMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PongBallMeshComponent->SetEnableGravity(false);
	PongBallMeshComponent->SetConstraintMode(EDOFMode::XYPlane);
	PongBallMeshComponent->SetCollisionProfileName("BlockAll");
	//PongBallMeshComponent->SetAngularDamping(0.0f);
	//PongBallMeshComponent->SetLinearDamping(0.0f);

	RootComponent = PongBallMeshComponent;
	
	PongBallCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("PongBallCollision"));
	PongBallCollisionComponent->SetupAttachment(RootComponent);
	PongBallCollisionComponent->SetCollisionProfileName("BlockAll");
	PongBallCollisionComponent->SetBoxExtent(PongBallCollisionBoxExtent);

}

// Called when the game starts or when spawned
void AC_PongBall::BeginPlay()
{
	Super::BeginPlay();
	
	//OnActorBeginOverlap.AddDynamic(this, &AC_PongBall::OnBallHit);
	PongBallMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AC_PongBall::OnBallHit);

}

// Called every frame
void AC_PongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_PongBall::Start()
{
	SetActorLocation(FVector::ZeroVector);
	FVector RandomVelocity = FVector((FMath::RandBool() ? 1.f : -1.f), (FMath::RandBool() ? 1.f : -1.f), 0) * PongBallMaxSpeedScale;
	PongBallMeshComponent->SetPhysicsLinearVelocity(RandomVelocity);
}

void AC_PongBall::OnBallHit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//void AC_PongBall::OnBallHit(AActor* OverlappedActor, AActor* OtherActor)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
	}

	APaddle* PongPaddle = Cast<APaddle>(OtherActor);
	AC_PongWall* PongGoal = Cast<AC_PongWall>(OtherActor);
	AC_PongGoal* PongWall = Cast<AC_PongGoal>(OtherActor);

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PongPaddle : %s"), IsValid(PongPaddle)));
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PongGoal : %s"), IsValid(PongGoal)));
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PongWall : %s"), IsValid(PongWall)));

}