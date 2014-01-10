#include "main_menu_state.h"
#include "../manager/gui_manager.h"

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
	musTheme.Unload();
}

void MainMenuState::OnStart(void *data)
{
	pSoundSystem->Unmute();

	UNUSED(data);
	Log("Entering MainMenu State");

	gGui->LoadGUI("gui/views/mainmenu.rml");

	musTheme.Load("sounds/menu_music.ogg");
	musTheme.SetVolume(1.0f);
	pSoundSystem->PlayMusic(&musTheme);
}

void MainMenuState::OnUpdate(f32 dt)
{
	UNUSED(dt);
}

void MainMenuState::OnStop(void *data)
{
	UNUSED(data);
	Log("Exiting MainMenu State");

	pSoundSystem->StopMusic();
	musTheme.Unload();
}
