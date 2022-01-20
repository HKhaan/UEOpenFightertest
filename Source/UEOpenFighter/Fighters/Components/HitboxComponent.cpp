#include "HitboxComponent.h"

#include "FighterComponent.h"
#include "AnimationComponent.h"
#include "BodyComponent.h"
#include "ComponentFactory.h"
#include "UEOpenFighter/ECF/World.h"

void HitboxComponent::Update(Entity* entity)
{
	//TODO: refactor needed;
	auto animator = (AnimationComponent*)entity->GetComponent(ComponentTypes::AnimationComponentType);
	if (animator != nullptr)
	{
		if(animator->InTransition()) return;
		FAnimations anim;
		for(auto animation : entity->FighterData->Animations)
		{
			if(animation.Id==animator->GetData()->AnimationId)
			{
				anim = animation;
				break;
			}
		}
		
		auto body = (BodyComponent*)entity->GetComponent(ComponentTypes::BodyComponentType);
		 if (body != nullptr && anim.Frames.Num()> animator->
		 	GetData()->CurrentFrame)
		 {
		 	for(auto hbox :anim.Frames[animator->GetData()->CurrentFrame].Hitboxes)
		 	{
		 		auto hitbox = hbox;
		 		hitbox.X += (int)body->GetData()->Position.X;
		 		hitbox.Y += (int)body->GetData()->Position.Z - (hitbox.RefHeight-hitbox.Height); // sets the anchor to the bottom.
		 			for (size_t i = 0; i < World::entities.size(); i++)
		 			{
		 				auto entities = World::entities.begin();
		 				std::advance(entities, i);
		 				if ((*entities) != entity)
		 				{
		 					auto enemyAnimator = (AnimationComponent*)(*entities)->GetComponent(
		 						ComponentTypes::AnimationComponentType);
		 					auto enemyBody = (BodyComponent*)(*entities)->GetComponent(ComponentTypes::BodyComponentType);
		 					if (enemyAnimator != nullptr && enemyBody !=
		 						nullptr)
		 					{
		 						FAnimations eAnim;
		 						for(auto animation : (*entities)->FighterData->Animations)
		 						{
		 							if(animation.Id==enemyAnimator->GetData()->AnimationId)
		 							{
		 								eAnim = animation;
		 								break;
		 							}
		 						}
		 						if(eAnim.Frames.Num()>enemyAnimator->GetData()->CurrentFrame){
		 						for(auto hubox :eAnim.Frames[enemyAnimator->GetData()->CurrentFrame].Hurtbox)
		 							{
		 							auto hurtbox = hubox;
		 							hurtbox.X += (int)enemyBody->GetData()->Position.X;
		 							hurtbox.Y += (int)enemyBody->GetData()->Position.Z - (hubox.RefHeight - hitbox.Height);// sets the anchor to the bottom.
		 							if (hitbox.X < hurtbox.X + hurtbox.Width &&
									 hitbox.X + hitbox.Width >  hurtbox.X &&
									 hitbox.Y <  hurtbox.Y + hurtbox.Height &&
									 hitbox.Height + hitbox.Y >  hurtbox.Y)
		 							{
		 								auto h1AAPos =body->GetData()->Position;
		 								auto h2AAPos = enemyBody->GetData()->Position;
		 								h2AAPos.Z = h1AAPos.Z;
		 								if(Vector3::Distance(h1AAPos,h2AAPos)< Fix(hitbox.Width+hurtbox.Width)/Fix(2)){
		 									(*entities)->SetState(EFightState::GotHit);
		 									UE_LOG(LogTemp, Warning, TEXT("hitting"));
		 								}
		 		
		 							}
		 							}
		 						}
		 				
		 					}
		 				}
		 			}
		 	}
		// 	auto hitbox = anim->GlobalHitbox;
		// 	hitbox.X += (int)body->GetData()->Position.X;
		// 	hitbox.Y += (int)body->GetData()->Position.Y;
		// 	for (size_t i = 0; i < World::entities.size(); i++)
		// 	{
		// 		auto entities = World::entities.begin();
		// 		std::advance(entities, i);
		// 		if ((*entities) != entity)
		// 		{
		// 			auto enemyAnimator = (AnimationComponent*)(*entities)->GetComponent(
		// 				ComponentTypes::AnimationComponentType);
		// 			auto enemyBody = (BodyComponent*)(*entities)->GetComponent(ComponentTypes::BodyComponentType);
		// 			if (enemyAnimator != nullptr && enemyAnimator->GetData()->Animation != nullptr && enemyBody !=
		// 				nullptr)
		// 			{
		// 				//TODO: Add fix for looking left/ looking right
		// 				auto hurtbox = enemyAnimator->GetData()->Animation->GlobalHurtbox;
		// 				hurtbox.X += (int)enemyBody->GetData()->Position.X;
		// 				hurtbox.Y += (int)enemyBody->GetData()->Position.Y;
		// 				if (hitbox.X < hurtbox.X + hurtbox.Width &&
		// 					hitbox.X + hitbox.Width >  hurtbox.X &&
		// 					hitbox.Y <  hurtbox.Y + hurtbox.Height &&
		// 					hitbox.Height + hitbox.Y >  hurtbox.Y)
		// 				{
		// 					//TODO: do a depth check.
		// 					(*entities)->GetData()->currentState = EFightState::GotHit;
		// 					UE_LOG(LogTemp, Warning, TEXT("hitting"));
		//
		// 				}
		// 			}
		// 		}
		// 	}
		 }

		if (entity->GetState() == EFightState::GotHit) {
			if (animator->GetData()->AnimationEnded) {
				entity->SetState(EFightState::Idle);
			}
		}
	}
}
