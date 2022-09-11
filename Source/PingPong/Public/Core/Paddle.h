// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Paddle.generated.h"


UCLASS()
class PINGPONG_API APaddle : public APawn
{
	GENERATED_BODY()

	APaddle(const FObjectInitializer& PCIP);

	virtual void Tick(float DeltaSeconds) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class APlayerController* SavedPlayerController;

	bool bIsCurrentlyPossessed = false;

public:	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* PaddleMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Box")
	class UBoxComponent* PaddleCollisionComponent;

	class UFloatingPawnMovement* PaddleMovementComponent;
	
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* PaddleMeshComponent;*/

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnPaddleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

	void PossessPaddle(APlayerController* PlayerController);

	// Input variables
	FVector CurrentVelocity;

	class ACameraActor* TopDownWorldCamera;

	FString CameraTagName = FString(TEXT("TopDownWorldCamera"));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Paddle Physics")
	float PaddleMaxSpeed = 1000.0f;

	FVector PaddleCollisionBoxExtent = FVector(175.f, 50.f, 50.f);
	FVector PaddleMeshScale = FVector(1.f, 0.5f, 0.2f);
	FVector PaddleMeshRelativeLocation = FVector(0.f, 0.f, -50.f);

	bool bIsOutOfBounds = false;

};
