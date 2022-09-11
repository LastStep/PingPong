// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PongBall.generated.h"

UCLASS()
class PINGPONG_API AC_PongBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_PongBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* PongBallMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Box")
	class UBoxComponent* PongBallCollisionComponent;

	void Start();
	//void OnBallHit(AActor* OverlappedActor, AActor* OtherActor);
	void OnBallHit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector PongBallCollisionBoxExtent = FVector(50.f, 50.f, 50.f);

	UPROPERTY(EditAnywhere, Category = "Physics")
	int PongBallMaxSpeedScale = 1000;
};
