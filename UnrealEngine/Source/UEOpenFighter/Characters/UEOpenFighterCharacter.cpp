// Fill out your copyright notice in the Description page of Project Settings.


#include "UEOpenFighterCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <UEOpenFighter/ECF/World.h>
#include <UEOpenFighter/ECF/Entity.h>
#include <UEOpenFighter/Actors/UEOpenFighterSpawner.h>
#include <UEOpenFighter/ECF/Components/BodyComponent.h>
#include <UEOpenFighter/ECF/Components/InputReceiverComponent.h>
#include <UEOpenFighter/ECF/Components/AnimationComponent.h>
#include <UEOpenFighter/ECF/Components/HitboxComponent.h>
#include <UEOpenFighter/ECF/Components/ComponentFactory.h>
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
	if (InEditor) return;
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
		Animator->PlayAnimation(&FighterData->Mobility.Idle);
	}
	Entity->Input = ((InputReceiverComponent*)ComponentFactory::AddComponent(
		Entity, ComponentTypes::InputReceiverComponentType));

	ComponentFactory::AddComponent(Entity, ComponentTypes::IdleComponentType);
	ComponentFactory::AddComponent(Entity, ComponentTypes::HitComponentType);
	ComponentFactory::AddComponent(Entity, ComponentTypes::WalkingComponentType);
	Entity->Input->GetData()->AssignedGamepad = PlayerIndex;
	Entity->Body->GetData()->Position = Vector3::FromFVector(cgmb->SpawnPoints[0]->GetActorLocation());
	if ((PlayerIndex+1)% 2 == 0) {
		Entity->Body->GetData()->Rotation.Z = Fix(270);
	}
	else {
		Entity->Body->GetData()->Rotation.Z = Fix(90);
	}
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
	Super::BeginPlay();
}

// Called every frame
void AUEOpenFighterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (InEditor) return;
	if (Animator != nullptr &&
		Animator->GetData()->Animation != nullptr
		&& Animator->GetData()->Animation != CurrentAnimation
		) {
		CurrentAnimation = Animator->GetData()->Animation;
		GetMesh()->PlayAnimation(Animator->GetData()->Animation->AnimatationAsset, false);
		GetMesh()->Stop();
	}
	GetMesh()->SetPosition(Animator->GetData()->CurrentFrame * 0.01667f);
	SetActorRotation(FRotator::MakeFromEuler(Entity->Body->GetData()->Rotation.ToFVector()));
}

// Called to bind functionality to input
void AUEOpenFighterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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

TArray<FVector> AUEOpenFighterCharacter::GetHurtboxes()
{
	auto positions = TArray<FVector>();
	int cnt = HitboxComponent::HurtboxCount(Entity);
	for (size_t i = 0; i < cnt; i++)
	{
		positions.Add(HitboxComponent::GetHurtboxPosition(Entity, i).ToFVector());
	}
	return positions;
}

TArray<FVector> AUEOpenFighterCharacter::GetHitboxes()
{
	auto positions = TArray<FVector>();
	int cnt = HitboxComponent::HitboxCount(Entity);
	for (size_t i = 0; i < cnt; i++)
	{
		positions.Add(HitboxComponent::GetHitboxPosition(Entity, i).ToFVector());
	}
	return positions;
}

