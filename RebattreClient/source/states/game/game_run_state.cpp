#include "game_run_state.h"
#include "../../manager/gui_manager.h"
#include "../../scene/game_scene.h"
#include "../../net/rs_client.h"

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

	// Start the game connection
	pRSClient->Connect();

	if (data)
	{
		GameScene *g = static_cast<GameScene *>(data);
		g->Resume();
	}
}

void GameRunState::OnUpdate(f32 dt)
{
	UNUSED(dt)
	pRSClient->Receive();
}

void GameRunState::OnStop(void *data)
{
	UNUSED(data)
	pRSClient->Disconnect();
	Log("Exiting GameRun State");
}
