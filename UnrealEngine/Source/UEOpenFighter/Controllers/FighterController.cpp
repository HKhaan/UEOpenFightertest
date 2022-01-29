// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterController.h"

#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#include "UEOpenFighter/ECF/Components/InputReceiverComponent.h"
#include "UEOpenFighter/Helpers/Convertors.h"

void AFighterController::BeginPlay()
{
	for (TActorIterator<ACameraActor> It(GetWorld()); It;)
	{
		CurrentView = (*It);
		SetViewTarget(CurrentView);
		FHitResult t;
		K2_SetActorLocation(CurrentView->GetActorLocation(),false,t,false);
		K2_SetActorRotation(CurrentView->GetActorRotation(),false);
		return;
	}
}


int32 AFighterController::GetInputKeyboard()
{
	static const struct
	{
		FKey key;
		uint32 input;
	} inputtable[] = {
			{EKeys::Up, EInputButtons::UpButton},
			{EKeys::Down, EInputButtons::DownButton},
			{EKeys::Left, EInputButtons::LeftButton},
			{EKeys::Right, EInputButtons::RightButton},
			{EKeys::D, EInputButtons::KickButton},
			{EKeys::S, EInputButtons::PunchButton},
		};
	int32 i, inputs = 0;

	for (i = 0; i < sizeof(inputtable) / sizeof(inputtable[0]); i++)
	{
		if (IsInputKeyDown(inputtable[i].key))
		{
			inputs |= inputtable[i].input;
		}
	}

	return inputs;
}

int32 AFighterController::GetInputGamepad()
{
	static const struct
	{
		FKey key;
		uint32 input;
	} inputtable[] = {
			{EKeys::Gamepad_DPad_Up, EInputButtons::UpButton},
			{EKeys::Gamepad_DPad_Down, EInputButtons::DownButton},
			{EKeys::Gamepad_DPad_Left, EInputButtons::LeftButton},
			{EKeys::Gamepad_DPad_Right, EInputButtons::RightButton},
			{EKeys::Gamepad_FaceButton_Right, EInputButtons::KickButton},
			{EKeys::Gamepad_FaceButton_Bottom, EInputButtons::PunchButton},
		};
	int32 i, inputs = 0;

	for (i = 0; i < sizeof(inputtable) / sizeof(inputtable[0]); i++)
	{
		if (IsInputKeyDown(inputtable[i].key))
		{
			inputs |= inputtable[i].input;
			if (inputs != 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("test"));
			}
		}
	}

	return inputs;
}

int32 AFighterController::GetInput(int index)
{
	return GetInputKeyboard() | GetInputGamepad();
}
