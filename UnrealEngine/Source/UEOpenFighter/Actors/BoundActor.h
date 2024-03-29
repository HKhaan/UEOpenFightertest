// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoundActor.generated.h"

UCLASS()
class UEOPENFIGHTER_API ABoundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoundActor();
	~ABoundActor();
	UStaticMeshComponent* Mesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="BoundActor")
	bool BoundX;
	FTimerHandle TimerHandle;
    void TickInEditor();
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="BoundActor")
	bool DestroyInBeginPlay;
	
};
