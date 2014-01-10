#include "game_run_state.h"
#include "../../manager/gui_manager.h"
#include "../../scene/game_scene.h"

GameRunState::GameRunState()
{
}

GameRunState::~GameRunState()
{
}

void GameRunState::OnStart(void *data)
{
	Log("Entering GameRun State");
	gGui->LoadGUI("gui/views/game.rml");

	if (data)
	{
		GameScene *g = static_cast<GameScene *>(data);
		g->Resume();
	}
}

void GameRunState::OnUpdate(f32 dt)
{
	UNUSED(dt)
}

void GameRunState::OnStop(void *data)
{
	UNUSED(data)
	Log("Exiting GameRun State");
}
