#include "trigger_entity.h"
#include "entity_factory.h"
#include "ball_entity.h"
#include "../scene/game_scene.h"
#include "../manager/gui_manager.h"

ENTITY_CREATOR("Trigger", TriggerEntity)

TriggerEntity::TriggerEntity()
	: Entity("Trigger")
{
}

TriggerEntity::~TriggerEntity()
{
}

void TriggerEntity::Load(Seed::MetadataObject &metadata, Seed::SceneNode *sprites)
{
	Entity::Load(metadata, sprites);
	clSensor.Load(metadata, this);
}

void TriggerEntity::OnCollision(const CollisionEvent &event)
{
	UNUSED(event);
//	Entity *other = event.GetOtherEntity();

	/*
	if(event.GetType() == CollisionEventType::OnEnter)
	{
		if(other != NULL && other->GetClassName().compare("Ball") == 0)
		{
			gGui->SetLeftPlayerPoints(gGui->GetLeftPlayerPoints() + 1);
		}
	}

	if(event.GetType() == CollisionEventType::OnLeave)
	{
		if(other != NULL && other->GetClassName().compare("Ball") == 0)
		{
			BallEntity *ball = static_cast<BallEntity*>(other);
			ball->Restart();
		}
	}
	*/
}
