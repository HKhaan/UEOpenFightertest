// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "UEOpenFighter/Data/Fighters.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Convertors.generated.h"



/**
 * 
 */
UCLASS()
class UEOPENFIGHTER_API UConvertors : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Convertors)
	static UFighters* CastToFighters(UObject* fighter)
	{
		return Cast<UFighters>(fighter);
	}
};

//TODO: create an helper class
template <typename T>
void FindAllActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<T> It(World); It; ++It)
	{
		Out.Add(*It);
	}
}

//TODO: create an helper class
int
fletcher32_checksum(short* data, size_t len);