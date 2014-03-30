#ifndef _PLAYER_ENTITY_H
#define _PLAYER_ENTITY_H

#include "sprite_entity.h"
#include "../defines.h"
#include <Box2D/Box2D.h>

class PlayerEntity: public SpriteEntity,
					public IEventInputKeyboardListener
{
	public:
		PlayerEntity();
		virtual ~PlayerEntity();

		virtual void Load(Seed::MetadataObject &metadata, Seed::SceneNode *sprites);
		virtual void Update(f32 dt);

		// IEventInputKeyboardListener
		virtual bool OnInputKeyboardPress(const EventInputKeyboard *ev);

		// IEventInputKeyboardListener
		virtual bool OnInputKeyboardRelease(const EventInputKeyboard *ev);

		Sprite *GetSprite() const;

	protected:
		b2Body		*pBody;
		float		fVelocity;
		b2Vec2		vDirection;
		bool		bKeyPressed;
};

#endif // _PLAYER_ENTITY_H
