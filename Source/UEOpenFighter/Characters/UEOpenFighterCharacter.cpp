// Fill out your copyright notice in the Description page of Project Settings.


#include "UEOpenFighterCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <UEOpenFighter/ECF/World.h>
#include <UEOpenFighter/ECF/Entity.h>
#include <UEOpenFighter/Actors/UEOpenFighterSpawner.h>
#include <UEOpenFighter/Fighters/Components/BodyComponent.h>
#include <UEOpenFighter/Fighters/Components/InputReceiverComponent.h>
#include <UEOpenFighter/Fighters/Components/AnimationComponent.h>
#include <UEOpenFighter/Fighters/Components/ComponentFactory.h>
#include <UEOpenFighter/UEOpenFighterGameModeBase.h>
#include "Camera/CameraActor.h"
#include "UEOpenFighter/Controllers/FighterController.h"
#include "UEOpenFighter/Physics/Shapes/Cylinder.h"

// Sets default values
AUEOpenFighterCharacter::AUEOpenFighterCharacter(const FObjectInitializer& ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//CreateDefaultSubobject<USceneComponent>
	//RootComponent = 
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;


}

// Called when the game starts or when spawned
void AUEOpenFighterCharacter::BeginPlay()
{
	Super::BeginPlay();
	auto cgmb = Cast<AUEOpenFighterGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	int PlayerIndex = cgmb->LastSpawnedPlayerIndex;
	Entity = World::CreateEntity();
	Entity->FighterData = FighterData;
	Entity->Actor = this;
	Entity->Body = ((BodyComponent*)ComponentFactory::AddComponent(Entity, ComponentTypes::BodyComponentType));
	Entity->Body->Shape = new Cylinder(35, 180);
	Animator = Entity->Animator = ((AnimationComponent*)ComponentFactory::AddComponent(
		Entity, ComponentTypes::AnimationComponentType));
	if (FighterData != nullptr) {
		Animator->GetData()->Animation = &FighterData->Mobility.Idle;
	}
	Entity->Input = ((InputReceiverComponent*)ComponentFactory::AddComponent(
		Entity, ComponentTypes::InputReceiverComponentType));

	ComponentFactory::AddComponent(Entity, ComponentTypes::IdleComponentType);
	ComponentFactory::AddComponent(Entity, ComponentTypes::WalkingComponentType);
	Entity->Input->GetData()->AssignedGamepad = PlayerIndex;
	Entity->Body->GetData()->Position = Vector3::FromFVector(cgmb->SpawnPoints[0]->GetActorLocation());
	for (auto spawnPoint : cgmb->SpawnPoints)
	{
		if (spawnPoint->PlayerIndex == PlayerIndex)
		{
			Entity->Body->GetData()->Position = Vector3::FromFVector(spawnPoint->GetActorLocation());
			break;
		}
	}
	Entity->Body->GetData()->Velocity.X = Fix(0);
	Entity->Body->GetData()->Velocity.Y = Fix(0);
	Entity->Body->GetData()->Velocity.Z = Fix(0);
}

// Called every frame
void AUEOpenFighterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Animator != nullptr &&
		Animator->GetData()->Animation != nullptr
		&& Animator->GetData()->Animation != CurrentAnimation
		) {
		GetMesh()->PlayAnimation(Animator->GetData()->Animation->AnimatationAsset, false);
		CurrentAnimation = Animator->GetData()->Animation;
	}
}

// Called to bind functionality to input
void AUEOpenFighterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AUEOpenFighterCharacter::ScheduleBakingFighter()
{
#if WITH_EDITOR
	if (Bake || AutoBake) {
		Bake = false;
		if (GetWorld()) {
			if (StartedBaking) {
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			}
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindLambda([this]
				{
					BakeFighter();
				});
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.0f, false, 0.5f);
			StartedBaking = true;
		}
	}
#endif
}

void AUEOpenFighterCharacter::BakeFighter()
{
#if WITH_EDITOR
	if (FighterData == nullptr) return;
	FighterData->BakeBones(GetMesh());
	FighterData->Modify(true);
	FighterData->PostEditChange();
	StartedBaking = false;
#endif
}

