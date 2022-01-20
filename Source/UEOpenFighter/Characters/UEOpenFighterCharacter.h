// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <UEOpenFighter/Fighters/Components/ComponentTypes.h>
#include "UEOpenFighter/Data/Fighters.h"
#include "UEOpenFighter/ECF/Entity.h"
#include "UEOpenFighter/Fighters/Components/InputReceiverComponent.h"
#include "UEOpenFighterCharacter.generated.h"

class Entity;





UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UEOPENFIGHTER_API AUEOpenFighterCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUEOpenFighterCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* MeshComponent;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	Entity* Entity;
	FORCEINLINE class USkeletalMeshComponent* GetMesh() const { return MeshComponent; }
};