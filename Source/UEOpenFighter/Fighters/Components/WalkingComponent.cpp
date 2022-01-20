#include "WalkingComponent.h"

#include "AnimationComponent.h"
#include "InputReceiverComponent.h"
#include "ComponentFactory.h"


#include "BodyComponent.h"
#include "KickComponent.h"
#include "FighterComponent.h"


void WalkingComponent::Update(Entity* entity)
{
	if(entity->Input&& entity->Input->GetData()->AssignedGamepad<0)
	{
		UE_LOG(LogTemp,Warning,TEXT("test"));
	}
	if (KickComponent::CheckShouldTransitionTo(entity)) return;
	bool moved = false;

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
		moved = true;
		entity->Body->GetData()->Velocity.Y = Fix(-10);
	}
	else if (entity->Input->IsPressed(EInputButtons::DownButton))
	{
		moved = true;
		entity->Body->GetData()->Velocity.Y = Fix(10);
	}
	else
	{
		entity->Body->GetData()->Velocity.Y = Fix(0);
	}
	if (!moved)
	{
		entity->SetState(EFightState::Idle);
	}
}

bool WalkingComponent::CheckShouldTransitionTo(Entity* entity)
{
	const int moveInputs = EInputButtons::RightButton|EInputButtons::LeftButton|EInputButtons::UpButton|EInputButtons::DownButton;
	if ((entity->Input->GetData()->Input & moveInputs) != 0) {
		entity->SetState(EFightState::Walking);
		return true;
	}
	return false;
}


