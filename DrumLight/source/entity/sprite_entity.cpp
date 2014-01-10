#include "sprite_entity.h"

#include "../scene/game_scene.h"
#include "../entity/entity_factory.h"

ENTITY_CREATOR("Sprite", SpriteEntity)

SpriteEntity::SpriteEntity():
	Entity("Sprite"),
	pSprite(NULL),
	pszSpriteName(NULL)
{
	//empty
}

SpriteEntity::SpriteEntity(const char *className, const char *spriteName)
	:	Entity(className)
	,	pSprite(NULL)
	,	pszSpriteName(spriteName)
{
	SEED_ASSERT(spriteName);
}

SpriteEntity::~SpriteEntity()
{
	gScene->Remove(pSprite);
	sdDelete(pSprite);
}

void SpriteEntity::Load(Seed::MetadataObject &metadata, Seed::SceneNode *sprites)
{
	Entity::Load(metadata, sprites);

	const char *spriteObject = pszSpriteName;
	String temp;
	if(spriteObject == NULL)
	{
		temp = metadata.GetProperty("Sprite");
		if(temp.empty())
		{
			Log("No sprite for SpriteEntity");
			return;
		}

		spriteObject = temp.c_str();
	}

	pSprite = sdNew(Sprite(*static_cast<Sprite *>(sprites->GetChildByName(spriteObject))));
	pSprite->SetPosition(metadata.GetPosition());

	gScene->Add(pSprite);
}

void SpriteEntity::SetPSZSprite(const char *spriteName)
{
	pszSpriteName = spriteName;
}

