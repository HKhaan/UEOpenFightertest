// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Characters/UEOpenFighterCharacter.h"
#include "Actors/UEOpenFighterSpawner.h"
#include "Data/Fighters.h"
#include "UEOpenFighterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UEOPENFIGHTER_API AUEOpenFighterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int LastSpawnedPlayerIndex;
	bool firstTick = false;
	void CreateBounds();

	//TODO: move this to ChorizoGameInstance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AUEOpenFighterCharacter> FighterActors;

	UPROPERTY()
		TArray<AUEOpenFighterSpawner*> SpawnPoints;

	int SpawnPointsCount = 0;
};
