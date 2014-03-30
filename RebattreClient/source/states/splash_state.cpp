#include "splash_state.h"
#include "../gameflow.h"
#include "../manager/gui_manager.h"
#include "../scene/game_scene.h"

SplashState::SplashState()
	: iBeginStateTime(0)
{
}

SplashState::~SplashState()
{
}

void SplashState::OnStart(void *data)
{
	UNUSED(data);
	Log("Entering Splash State");
	gGui->LoadGUI("gui/views/splash.rml");

	iBeginStateTime = pTimer->GetMilliseconds();
}

void SplashState::OnUpdate(f32 dt)
{
	UNUSED(dt);
	if (Milliseconds(iBeginStateTime + 3000) < pTimer->GetMilliseconds())
		gFlow->Menu();
}

void SplashState::OnStop(void *data)
{
	UNUSED(data);
	Log("Exiting GamePause State");
}
