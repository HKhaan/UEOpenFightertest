// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/UEOpenFighterCharacter.h"
#include "Data/Fighters.h"
#include "Engine/GameInstance.h"
#include "UEOpenFighterGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FMultiplayerEntities
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Port;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Ip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Local;
};

/**
 *
 */
UCLASS()
class UEOPENFIGHTER_API UUEOpenFighterGameInstance : public UGameInstance
{
	GENERATED_BODY()
		UUEOpenFighterGameInstance();
	virtual void Init() override;
public:
	void UTick();
	FTimerHandle TimerHandle_Tick;
	virtual void Shutdown() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Online;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Test;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PlayerCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AUEOpenFighterCharacter>> SelectedFighters;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMultiplayerEntities> MultiplayerEntities;
};
