#include "block_entity.h"

#include "entity_factory.h"

#include <SceneNode.h>
#include <Sprite.h>
#include "../scene/game_scene.h"
#include "../util/sounds.h"

ENTITY_CREATOR("Block", BlockEntity)

BlockEntity::BlockEntity()
	: SpriteEntity("Block", "Block")
{
}

BlockEntity::~BlockEntity()
{
	gPhysicsManager->DestroyBody(pBody);
}

void BlockEntity::Load(Seed::MetadataObject &metadata, Seed::SceneNode *sprites)
{
	SpriteEntity::Load(metadata, sprites);

	pBody = gPhysicsManager->CreateStaticBody(pSprite, BodyType::Normal, true, nullptr);
	pBody->SetFixedRotation(true);
	pBody->GetFixtureList()->SetUserData(this);
}

void BlockEntity::Restart()
{
}

Sprite *BlockEntity::GetSprite() const
{
	return pSprite;
}

void BlockEntity::Update(f32 dt)
{
	UNUSED(dt);
}
