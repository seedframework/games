#include "entity.h"

#include "../scene/game_scene.h"

Entity::Entity(const String &className)
	: strClassName(className)
{
}

Entity::~Entity()
{
}

void Entity::Load(IMetadataObject &metadata, SceneNode *sprites)
{
	UNUSED(sprites)
	strName = metadata.sName;

	strTarget = metadata.GetProperty("Target");
}

void Entity::DoActivateAll()
{
	if(!strTarget.empty())
		gWorldController->ActivateAllEntites(strTarget.c_str());
}
