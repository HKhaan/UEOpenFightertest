#include "WalkingComponent.h"

#include "AnimationComponent.h"
#include "InputReceiverComponent.h"
#include "ComponentFactory.h"


#include "BodyComponent.h"
#include "HitComponent.h"
#include "FighterComponent.h"


void WalkingComponent::Update(Entity* entity)
{
	bool twod = true;
	if (entity->Input && entity->Input->GetData()->AssignedGamepad < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("test"));
	}
	if (GetData()->Jumping) {
		if (GetData()->JumpVal < 16) {
			entity->Body->GetData()->Position.Z += Fix(GetData()->JumpVal)* Fix(1.75f);
		}
		else {
			entity->Body->GetData()->Position.Z += Fix(15 - GetData()->JumpVal) * Fix(1.75f);
		}
		if (GetData()->JumpVal >= 30) {
			GetData()->Jumping = false;
		}
		else {
			GetData()->JumpVal++;
			return;
		}
	}
	if (HitComponent::CheckShouldTransitionTo(entity)) return;
	bool moved = false;
	bool vertical = false;
	if (entity->Input->IsPressed(EInputButtons::LeftButton))
	{
		moved = true;
		entity->Body->GetData()->Velocity.X = Fix(-10);
	}
	else if (entity->Input->IsPressed(EInputButtons::RightButton))
	{
		moved = true;
		entity->Body->GetData()->Velocity.X = Fix(10);
	}
	else
	{
		entity->Body->GetData()->Velocity.X = Fix(0);
	}
	if (entity->Input->IsPressed(EInputButtons::UpButton))
	{
		if (twod) {
			GetData()->Jumping = true;
			GetData()->JumpVal = 0;
		}else{
			moved = true;
			entity->Body->GetData()->Velocity.Y = Fix(-10);
			vertical = true;
		}
	}
	else if (entity->Input->IsPressed(EInputButtons::DownButton) && !twod)
	{
		moved = true;
		entity->Body->GetData()->Velocity.Y = Fix(10);
		vertical = true;
	}
	else
	{
		entity->Body->GetData()->Velocity.Y = Fix(0);
	}
	if (!moved)
	{
		entity->SetState(EFightState::Idle);
	}
	else {
		auto pos = entity->Body->GetData()->Position;
		auto newPos = pos + entity->Body->GetData()->Velocity;
		auto newRot = pos.LookAt(newPos);
		if (false) {
			entity->Body->GetData()->Rotation = pos.LookAt(newPos);
			entity->Animator->PlayAnimation(&entity->FighterData->Mobility.Forward, false);
		}
		else {
			if(!vertical){
				auto dotp = Vector3::Dot(entity->Body->GetData()->Rotation.Forward(), entity->Body->GetData()->Velocity);
				if (dotp > Fix(2)) {
					entity->Animator->PlayAnimation(&entity->FighterData->Mobility.Forward, false);
				}
				else if (dotp < Fix(-2) && dotp != Fix(10)) {
					entity->Animator->PlayAnimation(&entity->FighterData->Mobility.Backward, false);
				}
			}
			else {
				auto dotp = Vector3::Dot(entity->Body->GetData()->Rotation.Right(), entity->Body->GetData()->Velocity);
				if (dotp > Fix(2)) {
					entity->Animator->PlayAnimation(&entity->FighterData->Mobility.TowardsCam, false);
				}
				else if (dotp < Fix(-2)) {
					entity->Animator->PlayAnimation(&entity->FighterData->Mobility.AwayFromCam, false);
				}
			}
		}
	}
}

bool WalkingComponent::CheckShouldTransitionTo(Entity* entity)
{
	const int moveInputs = EInputButtons::RightButton | EInputButtons::LeftButton | EInputButtons::UpButton | EInputButtons::DownButton;
	if ((entity->Input->GetData()->Input & moveInputs) != 0) {
		entity->SetState(EFightState::Walking);
		return true;
	}
	return false;
}


