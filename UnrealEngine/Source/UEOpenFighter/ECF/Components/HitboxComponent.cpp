#include "HitboxComponent.h"

#include "FighterComponent.h"
#include "AnimationComponent.h"
#include "BodyComponent.h"
#include "ComponentFactory.h"
#include "UEOpenFighter/ECF/World.h"
#include "AnimationComponent.h"
void HitboxComponent::Update(Entity* entity)
{
	//TODO: refactor needed;
	if (entity->GetState() == EFightState::Hit) {
		auto animator = (AnimationComponent*)entity->GetComponent(ComponentTypes::AnimationComponentType);

	}
}


int HitboxComponent::HurtboxCount(Entity* entity) {
	return entity->Animator->GetData()->Animation->Frames[entity->Animator->GetData()->CurrentFrame].Hurtbox.Num();
	
}

Vector3 HitboxComponent::GetHurtboxPosition(Entity* entity, int index) {
	auto f = entity->Animator->GetData()->Animation->Frames[entity->Animator->GetData()->CurrentFrame].Hurtbox[index].Position;
	auto pos = entity->Body->GetData()->Position;
	auto rot = entity->Body->GetData()->Rotation;
	rot.Z -= Fix(90);
	pos += (rot.Forward() * Fix(f.X));
	pos += (rot.Right() * Fix(f.Y));
	pos += (rot.Up() * Fix(f.Z));
	return pos;
}

int HitboxComponent::HitboxCount(Entity* entity) {
	return entity->Animator->GetData()->Animation->Frames[entity->Animator->GetData()->CurrentFrame].Hitboxes.Num();

}

Vector3 HitboxComponent::GetHitboxPosition(Entity* entity, int index) {
	auto f = entity->Animator->GetData()->Animation->Frames[entity->Animator->GetData()->CurrentFrame].Hitboxes[index].Position;
	auto pos = entity->Body->GetData()->Position;
	auto rot = entity->Body->GetData()->Rotation;
	rot.Z -= Fix(90);
	pos += (rot.Forward() * Fix(f.X));
	pos += (rot.Right() * Fix(f.Y));
	pos += (rot.Up() * Fix(f.Z));
	return pos;
}