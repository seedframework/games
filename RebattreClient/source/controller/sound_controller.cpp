#include "sound_controller.h"

SoundController::SoundController():
	pSounds(NULL)
{
	//empty
}

void SoundController::Init(SceneNode &sounds)
{
	pSounds = &sounds;
}

void SoundController::Play(const String &name)
{
	ISoundSource *source = static_cast<ISoundSource *>(pSounds->GetChildByName(name));

	if(source == NULL)
		return;

	source->Play();
}

void SoundController::Update(f32 dt)
{

}
