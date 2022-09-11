// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/C_GameModeBase.h"
#include "Core/Paddle.h"
#include "Actor/C_PongBall.h"
#include "Kismet/GameplayStatics.h"


void AC_GameModeBase::PostLogin(APlayerController* PlayerController)
{
	Super::PostLogin(PlayerController);

	TArray<AActor*> PawnArray;
	UGameplayStatics::GetAllActorsOfClass(this, APaddle::StaticClass(), PawnArray);
	if (PawnArray.Num() > 0)
	{
		for (AActor* Actor : PawnArray)
		{
			APaddle* Paddle = Cast<APaddle>(Actor);
			if (Paddle)
			{
				Paddle->PossessPaddle(PlayerController);
			}
		}
	}

	if (GetNumPlayers() == 1)
	{
		StartGame();
	}

}

void AC_GameModeBase::StartGame()
{
	TArray<AActor*> PongBallArray;
	UGameplayStatics::GetAllActorsOfClass(this, AC_PongBall::StaticClass(), PongBallArray);

	if (PongBallArray.Num() > 0 && IsValid(PongBallArray[0]))
	{
		ActivePongBall = Cast<AC_PongBall>(PongBallArray[0]);
		ActivePongBall->Start();
	}

	/*ActivePongBall = GetWorld()->SpawnActor<AC_PongBall>(AC_PongBall::StaticClass());
	if (IsValid(ActivePongBall)
	{
		ActivePongBall->Start();
	}*/
}