// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "include/ggponet.h"
#include "MultiplayerRunner.generated.h"

UCLASS()
class UEOPENFIGHTER_API AMultiplayerRunner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiplayerRunner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float Accumulator = 0.0f;
	//GGPOSessionCallbacks CreateCallbacks();
	bool __cdecl BeginGameCallbacl(const char*);
	bool __cdecl SaveGameStateCallback(unsigned char** buffer, int32* len, int32* checksum, int32);
	bool __cdecl LoadGameStateCallback(unsigned char* buffer, int32 len);
	bool __cdecl LogGameStateCallback(const char* filename, unsigned char* buffer, int len);
	void __cdecl FreeBuffer(void* buffer);
	//TArray<GGPOPlayerHandle> PlayerHandles;
	bool __cdecl AdvanceFrameCallback(int32);
	//bool __cdecl OnEventCallback(GGPOEvent* info);
//	GGPOSession* Ggpo = nullptr;
	void RunTick(TArray<int> inputs);
	int localIndex;
	int framesAhead=0;
	UPROPERTY()
	int NumPlayers = 0;
};
