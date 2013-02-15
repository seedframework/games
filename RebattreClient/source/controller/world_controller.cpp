#include "world_controller.h"
#include "../entity/entity_factory.h"
#include "../entity/entity.h"

WorldController::~WorldController()
{
	this->Clear();
}

Entity* WorldController::BuildEntity(IMetadataObject &metadata, SceneNode *sprites)
{
	const String &className = metadata.GetProperty("Class");

	Log("%s", className.c_str());

	Entity *ent = EntityFactory::CreateEntity(className);
	if (ent == NULL)
		return NULL;

	ent->Load(metadata, sprites);

	vEntities.push_back(ent);

	return ent;
}

void WorldController::Clear()
{
	for (EntitiesVector_t::iterator it = vEntities.begin(), end = vEntities.end(); it != end; ++it)
	{
		Delete(*it);
	}

	vEntities.clear();
}

void WorldController::Update(f32 dt)
{
	for (EntitiesVector_t::iterator it = vEntities.begin(), end = vEntities.end(); it != end; ++it)
	{
		(*it)->Update(dt);
	}
}

Entity *WorldController::FindEntityByClassName(const char *className)
{
	for (EntitiesVector_t::iterator it = vEntities.begin(), end = vEntities.end(); it != end; ++it)
	{
		if((*it)->GetClassName().compare(className) == 0)
		{
			return *it;
		}
	}

	return NULL;
}

Entity *WorldController::FindEntityByName(const char *name)
{
	for (EntitiesVector_t::iterator it = vEntities.begin(), end = vEntities.end(); it != end; ++it)
	{
		if((*it)->GetName().compare(name) == 0)
		{
			return *it;
		}
	}

	return NULL;
}

void WorldController::ActivateAllEntites(const char *name)
{
	for (EntitiesVector_t::iterator it = vEntities.begin(), end = vEntities.end(); it != end; ++it)
	{
		if((*it)->GetName().compare(name) == 0)
		{
			(*it)->Activate();
		}
	}
}



