// Fill out your copyright notice in the Description page of Project Settings.


#include "BoundActor.h"

// Sets default values
ABoundActor::ABoundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
    TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (mesh.Object)
	{
		Mesh->SetStaticMesh(mesh.Object);
	}

	if(GetWorld()){
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABoundActor::TickInEditor, 0.016f, true);
	}
}

ABoundActor::~ABoundActor()
{
	if(GetWorld()){
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
}

void ABoundActor::TickInEditor()
{
	Mesh->SetWorldRotation(FRotator::ZeroRotator);
	if(BoundX)
		Mesh->SetWorldScale3D(FVector(1.0f,100000.0f,1.0));
	else
		Mesh->SetWorldScale3D(FVector(100000.0f,1.0,1.0));
		
}
// Called when the game starts or when spawned
void ABoundActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABoundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(DestroyInBeginPlay)
	{
		Destroy();
	}
}

