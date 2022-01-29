// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FighterController.generated.h"

/**
 * 
 */
UCLASS()
class UEOPENFIGHTER_API AFighterController : public APlayerController
{
	GENERATED_BODY()
	public:
	virtual void BeginPlay() override;
	int32 GetInputKeyboard();
	int32 GetInputGamepad();
	int32 GetInput(int index);
	ACameraActor* CurrentView=nullptr;
};
