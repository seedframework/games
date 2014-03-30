#include "piece_entity.h"
#include "entity_factory.h"
#include "../scene/game_scene.h"

ENTITY_CREATOR("Piece", PieceEntity)

PieceEntity::PieceEntity()
	: SpriteEntity("Piece", "")
	, fVelocity(3.0f)
{
}

PieceEntity::~PieceEntity()
{
	pInput->RemoveKeyboardListener(this);
	gPhysicsManager->DestroyBody(pBody);
}

void PieceEntity::Load(MetadataObject &metadata, Seed::SceneNode *sprites)
{
	SpriteEntity::SetPSZSprite(metadata.sName.c_str());
	SpriteEntity::Load(metadata, sprites);

	b2Vec2 customSize(12, 56);

	pBody = gPhysicsManager->CreateBody(pSprite, &customSize);
	pBody->SetFixedRotation(true);
	pBody->GetFixtureList()->SetUserData(this);

	vDirection = VECTOR_ZERO;

	pInput->AddKeyboardListener(this);
}

Sprite *PieceEntity::GetSprite() const
{
	return pSprite;
}

void PieceEntity::Update(f32 dt)
{
	pBody->SetTransform(pBody->GetPosition() + ((fVelocity * dt) * vDirection), pBody->GetAngle());
}

bool PieceEntity::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == eKey::Up)
	{
		bKeyPressed = true;
		vDirection = VECTOR_ZERO;
		vDirection += VECTOR_UP;
	}

	if (k == eKey::Down)
	{
		bKeyPressed = true;
		vDirection = VECTOR_ZERO;
		vDirection += VECTOR_DOWN;
	}

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

	return true;
}

bool PieceEntity::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == eKey::Up)
	{
		bKeyPressed = false;
		vDirection -= VECTOR_UP;
		vDirection = VECTOR_ZERO;
	}

	if (k == eKey::Down)
	{
		bKeyPressed = false;
		vDirection -= VECTOR_DOWN;
		vDirection = VECTOR_ZERO;
	}

	if (k == eKey::Left)
	{
		bKeyPressed = true;
		vDirection += VECTOR_LEFT;
		vDirection = VECTOR_ZERO;
	}

	if (k == eKey::Right)
	{
		bKeyPressed = true;
		vDirection += VECTOR_RIGHT;
		vDirection = VECTOR_ZERO;
	}

	return true;
}
