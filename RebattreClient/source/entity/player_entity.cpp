#include <Box2D/Common/b2Math.h>
#include <SceneNode.h>
#include <Sprite.h>
#include "player_entity.h"
#include "entity_factory.h"
#include "../scene/game_scene.h"
#include "../util/sounds.h"
#include "../scene/game_scene.h"
#include "../net/rs_client.h"

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

	b2Vec2 customSize(12, 56);

	pBody = gPhysicsManager->CreateBody(pSprite, &customSize);
	pBody->SetFixedRotation(true);
	pBody->GetFixtureList()->SetUserData(this);

	vDirection = VECTOR_ZERO;

	// Send the initial position
	if ((pRSClient->iIDPlayer == pRSClient->PlayerOne && this->GetName() == "PlayerLeft")
		|| (pRSClient->iIDPlayer == pRSClient->PlayerTwo && this->GetName() == "PlayerRight"))
	{
		pRSClient->sPacketData.vRemotePlayer = pBody->GetPosition();
		pRSClient->cSocket.Send(pRSClient->GetAddress(), &pRSClient->sPacketData, sizeof(pRSClient->sPacketData));
	}

	pInput->AddKeyboardListener(this);
}

Sprite *PlayerEntity::GetSprite() const
{
	return pSprite;
}

void PlayerEntity::Update(f32 dt)
{
	if(pRSClient->iIDPlayer == pRSClient->PlayerOne && this->GetName() == "PlayerLeft")
	{
		pBody->SetTransform(pBody->GetPosition() + ((fVelocity * dt) * vDirection), pBody->GetAngle());
		if(bKeyPressed)
		{
			pRSClient->sPacketData.vRemotePlayer = pBody->GetPosition();
			pRSClient->cSocket.Send(pRSClient->GetAddress(), &pRSClient->sPacketData, sizeof(pRSClient->sPacketData));
		}
	}
	else if(pRSClient->iIDPlayer == pRSClient->PlayerTwo && this->GetName() == "PlayerRight")
	{
		pBody->SetTransform(pBody->GetPosition() + ((fVelocity * dt) * vDirection), pBody->GetAngle());
		if(bKeyPressed)
		{
			pRSClient->sPacketData.vRemotePlayer = pBody->GetPosition();
			pRSClient->cSocket.Send(pRSClient->GetAddress(), &pRSClient->sPacketData, sizeof(pRSClient->sPacketData));
		}
	}
	else
		pBody->SetTransform(pRSClient->vEnemyPlayer, pBody->GetAngle());
}

bool PlayerEntity::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == eKey::Up)
	{
		if ((pRSClient->iIDPlayer == pRSClient->PlayerOne && this->GetName() == "PlayerLeft")
		 || (pRSClient->iIDPlayer == pRSClient->PlayerTwo && this->GetName() == "PlayerRight"))
		{
			bKeyPressed = true;
			vDirection += VECTOR_UP;
		}
	}

	if (k == eKey::Down)
	{
		if ((pRSClient->iIDPlayer == pRSClient->PlayerOne && this->GetName() == "PlayerLeft")
		 || (pRSClient->iIDPlayer == pRSClient->PlayerTwo && this->GetName() == "PlayerRight"))
		{
			bKeyPressed = true;
			vDirection += VECTOR_DOWN;
		}
	}

	return true;
}

bool PlayerEntity::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == eKey::Up)
	{
		if ((pRSClient->iIDPlayer == pRSClient->PlayerOne && this->GetName() == "PlayerLeft")
		||  (pRSClient->iIDPlayer == pRSClient->PlayerTwo && this->GetName() == "PlayerRight"))
		{
			bKeyPressed = false;
			vDirection -= VECTOR_UP;
		}
	}

	if (k == eKey::Down)
	{
		if ((pRSClient->iIDPlayer == pRSClient->PlayerOne && this->GetName() == "PlayerLeft")
		||  (pRSClient->iIDPlayer == pRSClient->PlayerTwo && this->GetName() == "PlayerRight"))
		{
			bKeyPressed = false;
			vDirection -= VECTOR_DOWN;
		}
	}

	return true;
}
