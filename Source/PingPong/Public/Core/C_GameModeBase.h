// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_GameModeBase.generated.h"


UCLASS()
class PINGPONG_API AC_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartGame();
//	void EndGame();

protected:
	virtual void PostLogin(APlayerController* PlayerController) override;

public:
	class UCameraComponent* TopDownWorldCamera;

	class AC_PongBall* ActivePongBall;
};
