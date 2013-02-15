#ifndef _BALL_ENTITY_H_
#define _BALL_ENTITY_H_

#include "sprite_entity.h"
#include "../defines.h"

#include "../util/collision_sensor.h"
#include <Box2D/Box2D.h>

class PlayerEntity;

class BallEntity: public SpriteEntity
{
	public:
		BallEntity();

		virtual void Load(Seed::IMetadataObject &metadata, Seed::SceneNode *sprites);
		virtual void Update(f32 dt);

		Vector3f GetPosition();
		Sprite *GetSprite() const;
		void Restart();

	private:
		b2Body		*pBody;
		u32			uCurrentMoveState;
};

#endif // _BALL_ENTITY_H_
