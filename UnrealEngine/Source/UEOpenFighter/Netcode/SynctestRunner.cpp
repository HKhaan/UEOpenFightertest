// Fill out your copyright notice in the Description page of Project Settings.


#include "SynctestRunner.h"
#include <fstream>
#include <ostream>
#include <UEOpenFighter/ECF/VirtualMemory.h>
#include <UEOpenFighter/Controllers/FighterController.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <UEOpenFighter/ECF/World.h>
#include <UEOpenFighter/ECF/Components/ComponentFactory.h>
#include <UEOpenFighter/ECF/Components/InputReceiverComponent.h>
#include "EngineUtils.h"
#include "UEOpenFighter/UEOpenFighterGameInstance.h"
#include "UEOpenFighter/UEOpenFighterGameModeBase.h"
#include "UEOpenFighter/Helpers/Convertors.h"

GGPOSessionCallbacks ASynctestRunner::CreateCallbacks()
{
	GGPOSessionCallbacks cb = { 0 };

	cb.begin_game = std::bind(&ASynctestRunner::BeginGameCallbacl, this, std::placeholders::_1);
	cb.save_game_state = std::bind(&ASynctestRunner::SaveGameStateCallback, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
		std::placeholders::_4);
	cb.load_game_state = std::bind(&ASynctestRunner::LoadGameStateCallback, this,
		std::placeholders::_1, std::placeholders::_2);
	cb.log_game_state = std::bind(&ASynctestRunner::LogGameStateCallback, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	cb.free_buffer = std::bind(&ASynctestRunner::FreeBuffer, this, std::placeholders::_1);
	cb.advance_frame = std::bind(&ASynctestRunner::AdvanceFrameCallback, this, std::placeholders::_1);
	cb.on_event = std::bind(&ASynctestRunner::OnEventCallback, this, std::placeholders::_1);

	return cb;
}

// Sets default values
ASynctestRunner::ASynctestRunner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASynctestRunner::BeginPlay()
{
	Super::BeginPlay();
	NumPlayers =0;
	auto gameInstance = Cast<UUEOpenFighterGameInstance>(GetGameInstance());
	NumPlayers = gameInstance->PlayerCount;
	UE_LOG(LogTemp, Error, TEXT("NUM PLAYERS: %i"), NumPlayers);
	auto cb = CreateCallbacks();
	auto result = GGPONet::ggpo_start_synctest(&Ggpo, &cb, "vectorwar", NumPlayers, sizeof(int)*NumPlayers, 2);

	for (size_t i = 0; i < NumPlayers; i++)
	{
		GGPOPlayerHandle handle;
		auto ggpoplayer = new GGPOPlayer();
		ggpoplayer->type = GGPO_PLAYERTYPE_LOCAL;
		ggpoplayer->player_num = i+1;
		result = GGPONet::ggpo_add_player(Ggpo, ggpoplayer, &handle);
		PlayerHandles.Add(handle);
	}
}

// Called every frame
void ASynctestRunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Accumulator += DeltaTime;
	GGPOErrorCode result = GGPOErrorCode::GGPO_OK;
	int disconnect_flags;
	if (Accumulator > 0.016f) {
		
		int inputs[4] = { 0 };
		for (size_t i = 0; i < NumPlayers; i++)
		{
			auto fc = Cast<AFighterController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
			auto input = fc->GetInput(i);
			result = GGPONet::ggpo_add_local_input(Ggpo, PlayerHandles[i], &input, sizeof(input));
		}
		if (GGPO_SUCCEEDED(result)) {
			result = GGPONet::ggpo_synchronize_input(Ggpo, (void*)inputs, sizeof(int) * NumPlayers, &disconnect_flags);
			if (GGPO_SUCCEEDED(result)) {
				TArray<int> inps = { inputs[0], inputs[1], inputs[2], inputs[3]  };
				
				RunTick(inps);
				GGPONet::ggpo_advance_frame(Ggpo);
			}
		}
		Accumulator = 0;
		GGPONet::ggpo_idle(Ggpo, 1);
	}
}






bool ASynctestRunner::BeginGameCallbacl(const char*)
{
	return true;
}

bool ASynctestRunner::SaveGameStateCallback(unsigned char** buffer, int32* len, int32* checksum, int32)
{
	*len = VirtualMemory::memory.size();
	*buffer = (unsigned char*)malloc(*len);
	if (!*buffer)
	{
		return false;
	}
	memcpy(*buffer, &VirtualMemory::memory[0], *len);
	*checksum = fletcher32_checksum((short*)*buffer, *len / 2);
	return true;
}

bool ASynctestRunner::LoadGameStateCallback(unsigned char* buffer, int32 len)
{
	memcpy(&VirtualMemory::memory[0], buffer, len);
	return true;
}

bool ASynctestRunner::LogGameStateCallback(const char* filename, unsigned char* buffer, int len)
{
	return true;
}

void ASynctestRunner::FreeBuffer(void* buffer)
{
	free(buffer);
}

bool ASynctestRunner::AdvanceFrameCallback(int flag)
{
	int inputs[4] = { 0 };
	int disconnect_flags;
	GGPONet::ggpo_synchronize_input(Ggpo, (void*)inputs, sizeof(int) * NumPlayers, &disconnect_flags);
	TArray<int> inps = { inputs[0], inputs[1], inputs[2], inputs[3] };
	RunTick(inps);
	GGPONet::ggpo_advance_frame(Ggpo);
	return true;
}

bool ASynctestRunner::OnEventCallback(GGPOEvent* info)
{
	int progress;
	switch (info->code)
	{
	case GGPO_EVENTCODE_CONNECTED_TO_PEER:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_CONNECTED_TO_PEER"));
		break;
	case GGPO_EVENTCODE_SYNCHRONIZING_WITH_PEER:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_SYNCHRONIZING_WITH_PEER"));
		progress = 100 * info->u.synchronizing.count / info->u.synchronizing.total;
		break;
	case GGPO_EVENTCODE_SYNCHRONIZED_WITH_PEER:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_SYNCHRONIZED_WITH_PEER"));
		break;
	case GGPO_EVENTCODE_RUNNING:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_RUNNING"));

		break;
	case GGPO_EVENTCODE_CONNECTION_INTERRUPTED:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_CONNECTION_INTERRUPTED"));
		break;
	case GGPO_EVENTCODE_CONNECTION_RESUMED:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_CONNECTION_RESUMED"));

		break;
	case GGPO_EVENTCODE_DISCONNECTED_FROM_PEER:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_DISCONNECTED_FROM_PEER"));
		break;
	case GGPO_EVENTCODE_TIMESYNC:
		UE_LOG(LogTemp, Warning, TEXT("GGPO_EVENTCODE_TIMESYNC"));
		break;
	}
	return true;
}

void ASynctestRunner::RunTick(TArray<int> inputs)
{
	for (size_t i = 0; i < World::entities.size(); i++)
	{
		auto entities = World::entities.begin();
		std::advance(entities, i);
		if((*entities)->Input!=nullptr)
		{
			if((*entities)->Input->GetData()->AssignedGamepad>=0)
			{
				if(inputs.Num()>(*entities)->Input->GetData()->AssignedGamepad){
					(*entities)->Input->GetData()->Input = inputs[(*entities)->Input->GetData()->AssignedGamepad];
				}
			}
			
		}
	}
	World::Update();
}
