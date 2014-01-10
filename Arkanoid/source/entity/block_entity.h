#ifndef _BLOCK_ENTITY_H_
#define _BLOCK_ENTITY_H_

#include <Box2D/Box2D.h>
#include "../defines.h"
#include "sprite_entity.h"
#include "../util/collision_sensor.h"

class BlockEntity: public SpriteEntity
{
	public:
		BlockEntity();
		virtual ~BlockEntity();

		virtual void Load(Seed::MetadataObject &metadata, Seed::SceneNode *sprites);
		virtual void Update(f32 dt);
		//virtual void OnCollision(const CollisionEvent &event);

		Sprite *GetSprite() const;
		void Restart();


	private:
		b2Body		*pBody;
};

#endif // _BLOCK_ENTITY_H_
