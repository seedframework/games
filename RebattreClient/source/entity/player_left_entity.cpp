#include <Box2D/Common/b2Math.h>
#include <SceneNode.h>
#include <LeakReport.h>
#include <Sprite.h>

#include "player_left_entity.h"
#include "entity_factory.h"
#include "../scene/game_scene.h"
#include "../util/sounds.h"
#include "../scene/game_scene.h"
#include "../gameflow.h"

ENTITY_CREATOR("PlayerLeft", PlayerLeftEntity)

PlayerLeftEntity::PlayerLeftEntity()
	: SpriteEntity("PlayerLeft", "PlayerLeft")
	, uCurrentMoveState(STOP)
{
}

PlayerLeftEntity::~PlayerLeftEntity()
{
	pInput->RemoveKeyboardListener(this);
	gPhysicsManager->DestroyBody(pBody);
}

void PlayerLeftEntity::Load(Seed::IMetadataObject &metadata, Seed::SceneNode *sprites)
{
	SpriteEntity::Load(metadata, sprites);
	pSprite->SetZ(-10);

	b2Vec2 customSize(40, 46);

	pBody = gPhysicsManager->CreateBody(pSprite, b2_kinematicBody, ShapeForm::BOX, &customSize);
	pBody->SetFixedRotation(true);
	pBody->GetFixtureList()->SetUserData(this);

	pInput->AddKeyboardListener(this);
}

Vector3f PlayerLeftEntity::GetPosition()
{
	return pSprite->GetPosition();
}

b2Vec2 PlayerLeftEntity::GetBodyPosition() const
{
	return pBody->GetPosition();
}

Sprite *PlayerLeftEntity::GetSprite() const
{
	return pSprite;
}

void PlayerLeftEntity::Update(f32 dt)
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

void PlayerLeftEntity::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == Seed::KeyW)
		uCurrentMoveState = UP;

	if (k == Seed::KeyS)
		uCurrentMoveState = DOWN;
}

void PlayerLeftEntity::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == Seed::KeyW)
		uCurrentMoveState = STOP;

	if (k == Seed::KeyS)
		uCurrentMoveState = STOP;
}

bool PlayerLeftEntity::CheckBorderLimit()
{
	if(gPhysicsManager->RayCast(pBody, b2Vec2(0, 0.32f)))
		return true;
	if(gPhysicsManager->RayCast(pBody, b2Vec2(0.16f, 0.32f)))
		return true;
	if(gPhysicsManager->RayCast(pBody, b2Vec2(-0.16f, 0.32f)))
		return true;

	return false;
}

void PlayerLeftEntity::Activate()
{
	gFlow->SetRightPlayerPoints(gFlow->GetRightPlayerPoints() + 1);
	gFlow->DoLoad();
}

