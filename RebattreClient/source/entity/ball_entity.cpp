#include "ball_entity.h"
#include "entity_factory.h"

#include <SceneNode.h>
#include <LeakReport.h>
#include <Sprite.h>
#include "../scene/game_scene.h"
#include "../util/sounds.h"
#include "../net/rs_client.h"

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

		// Confirm ball position
//		pBody->SetTransform(pRSClient->sPacketData.vBall, pBody->GetAngle());

		// Normalize
		vDirection *= vDirection.Normalize();

		if(other == NULL)
		{
			// Invert diection
			vDirection.y *=-1;
		}
		if(other != NULL && other->GetName() == "PlayerRight")
		{
			// Invert diection
			vDirection.x *=-1;
		}

		if(other != NULL && other->GetName() == "PlayerLeft")
		{
			// Invert diection
			vDirection.x *=-1;
		}

		// Confirm ball position
//		pRSClient->sPacketData.vBall = pBody->GetPosition();
//		pRSClient->cSocket.Send(pRSClient->cAddress, &pRSClient->sPacketData, sizeof(pRSClient->sPacketData));
	}
}

