// Copyright Epic Games, Inc. All Rights Reserved.


#include "UEOpenFighterGameModeBase.h"


// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEOpenFighter/ECF/Components/AnimationComponent.h"
#include "UEOpenFighter/ECF/World.h"
#include "UEOpenFighter/Helpers/Convertors.h"
#include "UEOpenFighter/Physics/Shapes/Bound.h"
#include "Controllers/FighterController.h"
#include "ECF/Components/WalkingComponent.h"
#include "ECF/Components/BodyComponent.h"
#include "ECF/Components/ComponentFactory.h"
#include "ECF/Components/FighterComponent.h"
#include "ECF/Components/HitboxComponent.h"
#include "ECF/Components/InputReceiverComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Components/CapsuleComponent.h"
#include <UEOpenFighter/Characters/UEOpenFighterCharacter.h>
#include <UEOpenFighter/Netcode/SynctestRunner.h>
#include <UEOpenFighter/UEOpenFighterGameInstance.h>
#include "EngineUtils.h"
#include "Actors/BoundActor.h"
#include "Netcode/MultiplayerRunner.h"


//  this must be undone at the bottom of this file

void AUEOpenFighterGameModeBase::BeginPlay()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.Owner = this;
	VirtualMemory::Clear();
	World::componentTypes.clear();
	World::entities.clear();
	FindAllActors(GetWorld(), SpawnPoints);
	SpawnPointsCount = SpawnPoints.Num();
	auto gameInstance = Cast<UUEOpenFighterGameInstance>(GetGameInstance());
	gameInstance->PlayerCount = 0;
	// destroy the default player or else get "max players" error
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerActor = Iterator->Get();
		if (PlayerActor && PlayerActor->PlayerState && !MustSpectate(PlayerActor))
		{
			TArray<ULocalPlayer*> LocalPlayers = GetGameInstance()->GetLocalPlayers();
			GetGameInstance()->RemoveLocalPlayer(LocalPlayers[0]);
			if (PlayerActor->GetPawn()!=nullptr) {
				PlayerActor->GetPawn()->Destroy();
			}
			PlayerActor->Destroy();

		}
	}

	// spawn the players
	//int index= 0;
	for (auto spawn : SpawnPoints)
	{
		LastSpawnedPlayerIndex = spawn->PlayerIndex;
		DefaultPawnClass = gameInstance->SelectedFighters[gameInstance->PlayerCount];
		APlayerController* controller;
		if (spawn->PlayerIndex >= 0)
		{
			gameInstance->PlayerCount++;
			controller = UGameplayStatics::CreatePlayer(GetWorld(), LastSpawnedPlayerIndex, true);
		}
	}

	CreateBounds();
	if (gameInstance->Online)
	{
		GetWorld()->SpawnActor<AMultiplayerRunner>(AMultiplayerRunner::StaticClass(), FTransform(FVector(-999, -999, -999)), SpawnInfo);
	}
	else
	{
		GetWorld()->SpawnActor<ASynctestRunner>(ASynctestRunner::StaticClass(), FTransform(FVector(-999, -999, -999)), SpawnInfo);
	}

	firstTick = false;

}

void AUEOpenFighterGameModeBase::Tick(float DeltaSeconds)
{
}

void AUEOpenFighterGameModeBase::CreateBounds()
{
	TArray<ABoundActor*> bounds;
	TArray<Entity*> entities;
	FindAllActors(GetWorld(), bounds);
	for (auto bound : bounds)
	{
		auto entity = World::CreateEntity();
		entity->Body = ((BodyComponent*)ComponentFactory::AddComponent(entity, ComponentTypes::BodyComponentType));
		entities.Push(entity);
	}
	int index = 0;
	for (auto bound : bounds)
	{
		entities[index]->Body->Shape = new Bound(bound->BoundX);
		entities[index]->Body->GetData()->Position = Vector3::FromFVector(bound->GetActorLocation());
		index++;
	}
}

