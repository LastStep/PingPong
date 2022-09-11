// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Paddle.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"


APaddle::APaddle(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to be controlled by the lowest-numbered player
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	PaddleMeshComponent = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PaddleMesh"));
	//PaddleMeshComponent->SetRelativeLocation(PaddleMeshRelativeLocation);
	//PaddleMeshComponent->SetWorldScale3D(PaddleMeshScale);
	PaddleMeshComponent->SetCollisionProfileName("BlockAll");

	RootComponent = PaddleMeshComponent;

	/*PaddleCollisionComponent = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("PaddleCollision"));
	PaddleCollisionComponent->InitBoxExtent(PaddleCollisionBoxExtent);
	PaddleCollisionComponent->SetCollisionProfileName("BlockAll");
	PaddleCollisionComponent->SetupAttachment(RootComponent);*/

	PaddleMovementComponent = PCIP.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("PaddleMovement"));
	PaddleMovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();

	PaddleMeshComponent->OnComponentHit.AddDynamic(this, &APaddle::OnPaddleHit);
	PaddleMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APaddle::OnOverlapBegin);
	PaddleMeshComponent->OnComponentEndOverlap.AddDynamic(this, &APaddle::OnOverlapEnd);
}

void APaddle::OnPaddleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComponent != NULL))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
	}
}

void APaddle::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

void APaddle::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
	}
}

void APaddle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &APaddle::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &APaddle::Move_YAxis);
}

void APaddle::Move_XAxis(float AxisValue)
{
	AddMovementInput(FVector(1, 0, 0), AxisValue, true);
}

void APaddle::Move_YAxis(float AxisValue)
{
	//CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * PaddleMaxSpeed;
}

void APaddle::PossessPaddle(APlayerController* PlayerController)
{
	if (SavedPlayerController)
	{
		// unpossess first ( helps with multiplayer )
		SavedPlayerController->UnPossess();
	}
	if (!bIsCurrentlyPossessed)
	{	
		SavedPlayerController = PlayerController;
		PlayerController->Possess(Cast<APawn>(this));

		bIsCurrentlyPossessed = true;

		TArray<AActor*> CameraArray;
		UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName(CameraTagName), CameraArray);
		if (CameraArray.Num() > 0)
		{
			TopDownWorldCamera = Cast<ACameraActor>(CameraArray[0]);
			PlayerController->SetViewTargetWithBlend(TopDownWorldCamera);
		}
	}
}