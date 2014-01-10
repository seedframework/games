#ifndef _WORLD_MANAGER_H_
#define _WORLD_MANAGER_H_

#include "../defines.h"
#include "../entity/entity.h"
#include <vector>

class Entity;

class WorldManager
{
	public:
		Entity* BuildEntity(MetadataObject &metadata, SceneNode *sprites);
		~WorldManager();

		void Clear();

		void Update(f32 dt);

		Entity *FindEntityByClassName(const char *className);
		Entity *FindEntityByName(const char *name);

		void ActivateAllEntites(const char *name);

	private:
		typedef std::vector<Entity *> EntitiesVector_t;
		EntitiesVector_t vEntities;
};


#endif // _WORLD_MANAGER_H_
