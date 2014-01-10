#ifndef _BALL_ENTITY_H_
#define _BALL_ENTITY_H_

#include <Box2D/Box2D.h>
#include "../defines.h"
#include "sprite_entity.h"
#include "../util/collision_sensor.h"


class BallEntity: public SpriteEntity
{
	public:
		BallEntity();
		virtual ~BallEntity();

		virtual void Load(Seed::MetadataObject &metadata, Seed::SceneNode *sprites);
		virtual void Update(f32 dt);
		virtual void OnCollision(const CollisionEvent &event);

		Sprite *GetSprite() const;
		void Restart();

	private:
		b2Body				*pBody;
		f32					fSpeed;
		b2Vec2				vDirection;
};

#endif // _BALL_ENTITY_H_
