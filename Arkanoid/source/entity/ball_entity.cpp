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
	, fSpeed(1.0f)
{
}

BallEntity::~BallEntity()
{
	gPhysicsManager->DestroyBody(pBody);
}

void BallEntity::Load(Seed::MetadataObject &metadata, Seed::SceneNode *sprites)
{
	SpriteEntity::Load(metadata, sprites);
	b2Vec2 customSize(22, 22);

	pBody = gPhysicsManager->CreateBody(pSprite, &customSize);
	pBody->SetFixedRotation(true);
	pBody->GetFixtureList()->SetUserData(this);

	vDirection = b2Vec2(-1, -1);
}

void BallEntity::Restart()
{
	b2Vec2 pos = b2Vec2(0, 0);
	pBody->SetTransform(pos, pBody->GetAngle());
}

Sprite *BallEntity::GetSprite() const
{
	return pSprite;
}

void BallEntity::Update(f32 dt)
{
	pBody->SetTransform(pBody->GetPosition() + ((fSpeed * dt) * vDirection), pBody->GetAngle());
}

void BallEntity::OnCollision(const CollisionEvent &event)
{
	if (event.GetType() == CollisionEventType::OnEnter)
	{
		Entity *other = event.GetOtherEntity();

		// Normalize
		vDirection *= vDirection.Normalize();

		if(other == NULL || (other != NULL && other->GetName() == "PlayerLeft"))
		{
			// Invert diection
			vDirection.y *=-1;
		}

		if(	(other != NULL && other->GetName() == "PointBorderLeft") ||
			(other != NULL && other->GetName() == "PointBorderRight"))
		{
			// Invert diection
			vDirection.x *=-1;
		}
	}
}

