#include "trigger_entity.h"
#include "entity_factory.h"
#include "ball_entity.h"
#include "../scene/game_scene.h"

ENTITY_CREATOR("Trigger", TriggerEntity)

TriggerEntity::TriggerEntity()
	: Entity("Trigger")
{
}

void TriggerEntity::Load(Seed::IMetadataObject &metadata, Seed::SceneNode *sprites)
{
	Entity::Load(metadata, sprites);
	clSensor.Load(metadata, this);
}

void TriggerEntity::OnCollision(const CollisionEvent &event)
{
	Entity *other = event.GetOtherEntity();

	if(event.GetType() == CollisionEventType::ON_ENTER)
	{
		if(other != NULL && other->GetClassName().compare("Ball") == 0)
		{
			Log("ON_ENTER: Ball");
			this->DoActivateAll();
		}
	}

	if(event.GetType() == CollisionEventType::ON_LEAVE)
	{
		if(other != NULL && other->GetClassName().compare("Ball") == 0)
		{
			Log("ON_LEAVE: PointBorder");
			BallEntity *ball = static_cast<BallEntity*>(other);
			ball->Restart();
		}
	}
}
