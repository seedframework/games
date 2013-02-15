#ifndef _SOUND_CONTROLLER_H
#define _SOUND_CONTROLLER_H

#include "../defines.h"

class SoundController
{
	public:
		SoundController();
		void Init(SceneNode &sounds);
		void Play(const String &name);
		void Update(f32 dt);

	private:
		SceneNode *pSounds;
};

#endif // _SOUND_CONTROLLER_H
