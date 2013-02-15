#include <Box2D/Common/b2Math.h>
#include <SceneNode.h>
#include <LeakReport.h>
#include <Sprite.h>
#include "player_right_entity.h"
#include "entity_factory.h"
#include "../scene/game_scene.h"
#include "../util/sounds.h"
#include "../scene/game_scene.h"
#include "../gameflow.h"

ENTITY_CREATOR("PlayerRight", PlayerRightEntity)

PlayerRightEntity::PlayerRightEntity()
	: SpriteEntity("PlayerRight", "PlayerRight")
	, uCurrentMoveState(STOP)
{
}

PlayerRightEntity::~PlayerRightEntity()
{
	pInput->RemoveKeyboardListener(this);
	gPhysicsManager->DestroyBody(pBody);
}

void PlayerRightEntity::Load(Seed::IMetadataObject &metadata, Seed::SceneNode *sprites)
{
	SpriteEntity::Load(metadata, sprites);
	pSprite->SetZ(-10);

	b2Vec2 customSize(40, 46);

	pBody = gPhysicsManager->CreateBody(pSprite, b2_kinematicBody, ShapeForm::BOX, &customSize);
	pBody->SetFixedRotation(true);
	pBody->GetFixtureList()->SetUserData(this);

	pInput->AddKeyboardListener(this);
}

Vector3f PlayerRightEntity::GetPosition()
{
	return pSprite->GetPosition();
}

b2Vec2 PlayerRightEntity::GetBodyPosition() const
{
	return pBody->GetPosition();
}

Sprite *PlayerRightEntity::GetSprite() const
{
	return pSprite;
}

void PlayerRightEntity::Update(f32 dt)
{
	UNUSED(dt);

	b2Vec2 vel = pBody->GetLinearVelocity();
	b2Vec2 pos = pBody->GetPosition();

	switch (uCurrentMoveState)
	{
		case UP:	vel.y = /*pos.y >= 37 ? 0 :*/ -5; break;
		case STOP:	vel.y = 0; break;
		case DOWN:	vel.y = /*pos.y <= 3 ? 0 :*/ 5; break;
	}

	pBody->SetLinearVelocity(vel);
}

void PlayerRightEntity::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == Seed::KeyUp)
		uCurrentMoveState = UP;

	if (k == Seed::KeyDown)
		uCurrentMoveState = DOWN;
}

void PlayerRightEntity::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == Seed::KeyUp)
		uCurrentMoveState = STOP;

	if (k == Seed::KeyDown)
		uCurrentMoveState = STOP;
}

bool PlayerRightEntity::CheckBorderLimit()
{
	if(gPhysicsManager->RayCast(pBody, b2Vec2(0, 0.32f)))
		return true;
	if(gPhysicsManager->RayCast(pBody, b2Vec2(0.16f, 0.32f)))
		return true;
	if(gPhysicsManager->RayCast(pBody, b2Vec2(-0.16f, 0.32f)))
		return true;

	return false;
}

void PlayerRightEntity::Activate()
{
	gFlow->SetLeftPlayerPoints(gFlow->GetLeftPlayerPoints() + 1);
	gFlow->DoLoad();
}

