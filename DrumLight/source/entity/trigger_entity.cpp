#include "trigger_entity.h"
#include "entity_factory.h"
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

void TriggerEntity::Load(MetadataObject &metadata, Seed::SceneNode *sprites)
{
	Entity::Load(metadata, sprites);
	clSensor.Load(metadata, this);
}

void TriggerEntity::OnCollision(const CollisionEvent &event)
{
}
