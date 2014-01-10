#ifndef _PIECE_ENTITY_H_
#define _PIECE_ENTITY_H_

#include "sprite_entity.h"

class PieceEntity : public SpriteEntity,
					public IEventInputKeyboardListener
{
	public:
		PieceEntity();
		virtual ~PieceEntity();

		virtual void Load(Seed::MetadataObject &metadata, Seed::SceneNode *sprites);
		virtual void Update(f32 dt);

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardPress(const EventInputKeyboard *ev);

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardRelease(const EventInputKeyboard *ev);

		Sprite *GetSprite() const;

	protected:
		b2Body		*pBody;
		float		fVelocity;
		b2Vec2		vDirection;
		bool		bKeyPressed;
};

#endif // _PIECE_ENTITY_H_
