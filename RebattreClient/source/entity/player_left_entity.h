#ifndef _PLAYER_LEFT_ENTITY_H
#define _PLAYER_LEFT_ENTITY_H

#include "sprite_entity.h"
#include "../defines.h"
#include <Box2D/Box2D.h>

class PlayerLeftEntity: public SpriteEntity,
					public IEventInputKeyboardListener
{
	public:
		PlayerLeftEntity();
		virtual ~PlayerLeftEntity();

		virtual void Load(Seed::IMetadataObject &metadata, Seed::SceneNode *sprites);
		virtual void Update(f32 dt);

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardPress(const EventInputKeyboard *ev);

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardRelease(const EventInputKeyboard *ev);

		virtual void Activate();

		Vector3f GetPosition();
		Sprite *GetSprite() const;
		b2Vec2 GetBodyPosition() const;

	private:
		bool CheckBorderLimit();

	protected:
		b2Body		*pBody;
		enum		eMoveStates {UP = 0, STOP = 1, DOWN = 2};
		u32			uCurrentMoveState;
};

#endif // _PLAYER_LEFT_ENTITY_H
