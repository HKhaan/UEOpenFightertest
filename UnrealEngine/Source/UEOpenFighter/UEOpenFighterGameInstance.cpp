// Fill out your copyright notice in the Description page of Project Settings.


#include "UEOpenFighterGameInstance.h"

#include <fstream>


UUEOpenFighterGameInstance::UUEOpenFighterGameInstance()
{

}

void UUEOpenFighterGameInstance::Init()
{

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Tick, this, &UUEOpenFighterGameInstance::UTick, 1.0f, true, 0.0f);
}


void UUEOpenFighterGameInstance::UTick()
{
}


void UUEOpenFighterGameInstance::Shutdown()
{
	Super::Shutdown();
}


