#include "BodyComponent.h"
#include <UEOpenFighter/ECF/World.h>
#include <list>
#include <UEOpenFighter/Characters/UEOpenFighterCharacter.h>
#include <UEOpenFighter/Fighters/Components/ComponentFactory.h>
#include <UEOpenFighter/ECF/Entity.h>
void BodyComponent::BeginPlay(Entity* entity)
{
}

void BodyComponent::Update(Entity* entity)
{
	//TODO: create new component for this
	if(entity->GetData()->Channel1.Sound && entity->GetData()->Channel1.CurrentFrame<3600)
	{
		entity->GetData()->Channel1.CurrentFrame++;
	}

	
	Shape->Position = &GetData()->Position;
	//
	// auto oldPos = GetData()->Position;
	// GetData()->Position.X += GetData()->Velocity.X;
	// GetData()->Position.Y += GetData()->Velocity.Y;
	//FixStageCollisions();
	// if (CheckPositionCollides(entity)) {
	// 	//TODO: impulse out instead of going back to oldpos
	// 	GetData()->Position = oldPos;
	// }
	//
	// //Friction
	// GetData()->Velocity.Y*=Fix(0.95f);
	// GetData()->Velocity.X*=Fix(0.95f);
	// if (FMath::Abs(GetData()->Velocity.Y) < Fix(0.001f)) GetData()->Velocity.Y = Fix(0);
	// if (FMath::Abs(GetData()->Velocity.X) < Fix(0.001f)) GetData()->Velocity.X = Fix(0);

	if(entity->Actor){
		FVector loc = GetData()->Position.ToFVector();
		//Pixel snap to grid
		loc /=2.0f;
		loc.X=FMath::RoundToFloat(loc.X)*2.0f;
		loc.Y=FMath::RoundToFloat(loc.Y)*2.0f;
		loc.Z=FMath::RoundToFloat(loc.Z)*2.0f;
		entity->Actor->SetActorLocation(loc,false);
	}
}

// bool BodyComponent::CheckPositionCollides(Entity* entity)
// {
// 	for (size_t i = 0; i < World::entities.size(); i++)
// 	{
// 		auto entities = World::entities.begin();
// 		std::advance(entities, i);
// 		if ((*entities) != entity) {
// 			auto b =(BodyComponent*)(*entities)->GetComponent(ComponentTypes::BodyComponentType);
// 			if (Vector3::Distance(b->GetData()->Position, GetData()->Position) < Fix(30)) {
// 				return true;
// 			}
// 		}
// 	}
// 	
// 	return false;
// }

Vector3 BodyComponent::PredictPosition(Entity* ent, int frames)
{
	auto velocity = ent->Body->GetData()->Velocity / Fix(World::PhysicsPrecision);
	auto startPos = ent->Body->GetData()->Position;
	for (int i = 0; i < World::PhysicsPrecision; i++)
	{
		ent->Body->GetData()->Position+=velocity;
		for(auto ent2: World::entities)
		{
			if(!ent2->GetData()->active) continue;
			if(ent==ent2) continue;
			if(ent->Body->Shape->Collides(ent2->Body->Shape))
			{
				auto predictPos = ent->Body->GetData()->Position;
				ent->Body->GetData()->Position = startPos;
				return predictPos;
			}
		}
	}
	auto predictPos = ent->Body->GetData()->Position;
	ent->Body->GetData()->Position = startPos;
	return predictPos;
}


BodyComponent::~BodyComponent()
{
	if(Shape!=nullptr)
	{
		delete Shape;
	}
}
