#include "ball_entity.h"
#include "entity_factory.h"

#include <SceneNode.h>
#include <LeakReport.h>
#include <Sprite.h>
#include "../scene/game_scene.h"
#include "../util/sounds.h"

ENTITY_CREATOR("Ball", BallEntity)

BallEntity::BallEntity()
	: SpriteEntity("Ball", "Ball")
{
}

void BallEntity::Load(Seed::IMetadataObject &metadata, Seed::SceneNode *sprites)
{
	SpriteEntity::Load(metadata, sprites);

	pBody = gPhysicsManager->CreateBody(pSprite, b2_dynamicBody, ShapeForm::CIRCLE);
	pBody->SetFixedRotation(true);
	pBody->GetFixtureList()->SetUserData(this);
	pBody->ApplyLinearImpulse(b2Vec2(-10, 5), pBody->GetPosition());
}

void BallEntity::Restart()
{
	pBody->SetLinearVelocity(b2Vec2(0,0));
	pBody->SetAngularVelocity(0);

	pBody->SetTransform(b2Vec2(0, 0), 0.0f);
	pBody->ApplyLinearImpulse(b2Vec2(-10, 5), pBody->GetPosition());
}

Vector3f BallEntity::GetPosition()
{
	return pSprite->GetPosition();
}

Sprite *BallEntity::GetSprite() const
{
	return pSprite;
}

void BallEntity::Update(f32 dt)
{
	UNUSED(dt)
}

