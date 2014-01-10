#include "game_pause_state.h"
#include "../../manager/gui_manager.h"
#include "../../scene/game_scene.h"

GamePauseState::GamePauseState()
{
}

GamePauseState::~GamePauseState()
{
}

void GamePauseState::OnStart(void *data)
{
	Log("Entering GamePause State");
	gGui->LoadGUI("gui/views/gamepause.rml");
	pSoundSystem->Mute();
	GameScene *g = static_cast<GameScene *>(data);
	g->Pause();
}

void GamePauseState::OnUpdate(f32 dt)
{
	UNUSED(dt)
}

void GamePauseState::OnStop(void *data)
{
	UNUSED(data)
	Log("Exiting GamePause State");
	pSoundSystem->Unmute();
}
