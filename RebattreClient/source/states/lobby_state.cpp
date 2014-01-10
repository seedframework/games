#include "lobby_state.h"
#include "../manager/gui_manager.h"

LobbyState::LobbyState()
{
}

LobbyState::~LobbyState()
{
}

void LobbyState::OnStart(void *data)
{
	UNUSED(data);
	Log("Entering Lobby State");
	gGui->LoadGUI("gui/views/lobby.rml");
}

void LobbyState::OnUpdate(f32 dt)
{
	UNUSED(dt);
}

void LobbyState::OnStop(void *data)
{
	UNUSED(data);
	Log("Exiting Lobby State");
	pSoundSystem->StopMusic();
}

