// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "UEOpenFighterSpawner.generated.h"

class UPaperFlipbookComponent;
/**
 * 
 */
UCLASS()
class UEOPENFIGHTER_API AUEOpenFighterSpawner : public APlayerStart
{
	GENERATED_BODY()
public:
	AUEOpenFighterSpawner(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int PlayerIndex;
	protected:
	
	virtual void BeginPlay() override;
	// UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	// UPaperFlipbookComponent* Sprite;
	// UPROPERTY()
	// UBillboardComponent* Root;
};
