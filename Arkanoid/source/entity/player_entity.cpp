#include <Box2D/Common/b2Math.h>
#include <SceneNode.h>
#include <LeakReport.h>
#include <Sprite.h>
#include "player_entity.h"
#include "entity_factory.h"
#include "../scene/game_scene.h"
#include "../util/sounds.h"
#include "../scene/game_scene.h"

ENTITY_CREATOR("Player", PlayerEntity)

PlayerEntity::PlayerEntity()
	: SpriteEntity("Player", "")
	, fVelocity(3.0f)
{
}

PlayerEntity::~PlayerEntity()
{
	pInput->RemoveKeyboardListener(this);
	gPhysicsManager->DestroyBody(pBody);
}

void PlayerEntity::Load(Seed::MetadataObject &metadata, Seed::SceneNode *sprites)
{
	SpriteEntity::SetPSZSprite(metadata.sName.c_str());
	SpriteEntity::Load(metadata, sprites);

	b2Vec2 customSize(56, 12);

	pBody = gPhysicsManager->CreateStaticBody(pSprite, BodyType::Normal, true, &customSize);
	pBody->SetFixedRotation(true);
	pBody->GetFixtureList()->SetUserData(this);

	vDirection = VECTOR_ZERO;

	pInput->AddKeyboardListener(this);
}

Sprite *PlayerEntity::GetSprite() const
{
	return pSprite;
}

void PlayerEntity::Update(f32 dt)
{
	pBody->SetTransform(pBody->GetPosition() + ((fVelocity * dt) * vDirection), pBody->GetAngle());
}

void PlayerEntity::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == eKey::Left)
	{
		bKeyPressed = true;
		vDirection = VECTOR_ZERO;
		vDirection += VECTOR_LEFT;
	}

	if (k == eKey::Right)
	{
		bKeyPressed = true;
		vDirection = VECTOR_ZERO;
		vDirection += VECTOR_RIGHT;
	}
}

void PlayerEntity::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == eKey::Left)
	{
		bKeyPressed = false;
		vDirection -= VECTOR_LEFT;
	}

	if (k == eKey::Right)
	{
		bKeyPressed = false;
		vDirection -= VECTOR_RIGHT;
	}

	vDirection = VECTOR_ZERO;
}
