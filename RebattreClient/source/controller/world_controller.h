#ifndef _WORLD_CONTROLLER_H_
#define _WORLD_CONTROLLER_H_

#include "../defines.h"
#include "../entity/entity.h"
#include <vector>

class Entity;

class WorldController
{
	public:
		Entity* BuildEntity(IMetadataObject &metadata, SceneNode *sprites);
		~WorldController();

		void Clear();

		void Update(f32 dt);

		Entity *FindEntityByClassName(const char *className);
		Entity *FindEntityByName(const char *name);

		void ActivateAllEntites(const char *name);

	private:
		typedef std::vector<Entity *> EntitiesVector_t;
		EntitiesVector_t vEntities;
};


#endif // _WORLD_CONTROLLER_H_
