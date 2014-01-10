#include "gameflow.h"
#include "scene/game_scene.h"
#include "manager/gui_manager.h"

#include <Rocket/Debugger.h>
#include <Rocket/Controls.h>

#define GAME_ID	0xF0000001

GameFlow *gFlow = NULL;
GameData *gGameData = NULL;

GameFlow::GameFlow()
	: pScene(NULL)
	, pCamera(NULL)
	, sSceneFile("")
{
	gFlow = this;
}

GameFlow::~GameFlow()
{
	gFlow = NULL;
}

bool GameFlow::Initialize()
{
	return cPres.Load("configs/game.config", [&](Presentation *, Renderer *)
	{
		// Create the transitions
		cSplashToMenu.Initialize(&cSplash, &cOnMenu, &cMenu);
		cMenuToGame.Initialize(&cMenu, &cOnGame, &cGame);
		cMenuToOptions.Initialize(&cMenu, &cOnOptions, &cOptions);
		cMenuToCredits.Initialize(&cMenu, &cOnCredits, &cCredits);
		cOptionsToMenu.Initialize(&cOptions, &cOnMenu, &cMenu);
		cCreditsToMenu.Initialize(&cCredits, &cOnMenu, &cMenu);
		cGameToMenu.Initialize(&cGame, &cOnMenu, &cMenu);
		cGameToLoad.Initialize(&cGame, &cOnLoad, &cLoad);
		cLoadToGame.Initialize(&cLoad, &cOnGame, &cGame);

		// Create the State Machine.
		cFlow.RegisterTransition(&cSplashToMenu);
		cFlow.RegisterTransition(&cMenuToGame);
		cFlow.RegisterTransition(&cMenuToOptions);
		cFlow.RegisterTransition(&cMenuToCredits);
		cFlow.RegisterTransition(&cOptionsToMenu);
		cFlow.RegisterTransition(&cCreditsToMenu);
		cFlow.RegisterTransition(&cGameToMenu);
		cFlow.RegisterTransition(&cGameToLoad);
		cFlow.RegisterTransition(&cLoadToGame);

		pSoundSystem->SetMusicVolume(0.6f);
		pSoundSystem->SetSfxVolume(0.5f);

		pSystem->AddListener(this);
		pInput->AddKeyboardListener(this);

		pScene = cPres.GetRendererByName("MainRenderer")->GetScene();
		Viewport *viewport = cPres.GetViewportByName("MainView");

		pCamera = viewport->GetCamera();

		sdNew(GuiManager());
		gGui->Initialize();
		pScene->Add(gGui->GetSceneObject());

		cFlow.Initialize(&cSplash);

		pSplashImg = (Image *)pScene->GetChildByName("SplashImage");
		pSplashImg->SetVisible(true);

		// Create the State Machine Data
		gGameData = sdNew(GameData());

		if (this->SaveSystemFlow())
			pSaveSystem->Load(0, &gGameData->sPlayer, &gGameData->sOptions);

		IGameApp::Initialize();
	});
}

bool GameFlow::Update(f32 dt)
{
	cFlow.Update(dt);
	cGame.LateStop();
	return true;
}

bool GameFlow::Shutdown()
{
	cMenu.OnStop(NULL);
	pSaveSystem->Save(0, &gGameData->sPlayer, &gGameData->sOptions);

	if (cFlow.GetCurrentState() == &cGame)
	{
		cGame.OnStop(NULL);
		cGame.LateStop();
	}

	pInput->RemoveKeyboardListener(this);
	pSystem->RemoveListener(this);

	pScene->Remove(gGui->GetSceneObject());
	gGui->Shutdown();
	sdDelete(gGui);

	cPres.Unload();

	sdDelete(gGameData);

	return IGameApp::Shutdown();
}

void GameFlow::Credits()
{
	cFlow.OnEvent(&cOnCredits);
}

void GameFlow::Options()
{
	cFlow.OnEvent(&cOnOptions);
}

void GameFlow::Menu()
{
	pSplashImg = (Image *)pScene->GetChildByName("SplashImage");
	pSplashImg->SetVisible(false);

	cFlow.OnEvent(&cOnMenu);
}

void GameFlow::OnSystemShutdown(const EventSystem *ev)
{
	UNUSED(ev)
	pSystem->Shutdown();
}

void GameFlow::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == eKey::Escape && cFlow.GetCurrentState() == &cMenu)
		pSystem->Shutdown();
	else if (k == eKey::F1)
		pResourceManager->Print();
	else if (k == eKey::F2)
		pResourceManager->GarbageCollect();
	else if (k == eKey::F4)
		pScene->Dump();
	else if (k == eKey::F5)
		gGui->ReloadGUI();
	else if (k == eKey::F6)
		Rocket::Debugger::SetVisible(!Rocket::Debugger::IsVisible());
}

void GameFlow::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	UNUSED(ev);
}

void GameFlow::LoadSceneFile(const String &file)
{
	sSceneFile = file;
	cFlow.OnEvent(&cOnLoad);
}

const String &GameFlow::GetSceneFile() const
{
	return sSceneFile;
}

void GameFlow::DoLoad(const String &scene)
{
	if (scene != "")
		sSceneFile = scene;

	if (sSceneFile != "")
	{
		cFlow.OnEvent(&cOnGame);
		sSceneFile = "";
	}
}

bool GameFlow::SaveSystemFlow() const
{
	GameData data;
	pSaveSystem->SetTotalSlots(4);

	eCartridgeError error = pSaveSystem->Initialize(eCartridgeSize::Tiny);
	if (error == eCartridgeError::None)
		error = pSaveSystem->Prepare(GAME_ID, &data.sPlayer, sizeof(data.sPlayer), &data.sOptions, sizeof(data.sOptions));

	if (error == eCartridgeError::DeviceFull)
	{
		Log("Not enough space available on device.");
		return false;
	}

	if (error == eCartridgeError::InodeFull)
	{
		Log("Not enough inodes available on device.");
		return false;
	}

	if (error == eCartridgeError::NoCard || error == eCartridgeError::AccessDenied)
	{
		Log("Unknown file system error - no card or access denied - system hungup");
		pSystem->HangUp();
		return false;
	}

	if (error == eCartridgeError::NotFormatted)
	{
		Log("Save file doesn't exist or corrupted, creating one now.");
		error = pSaveSystem->FormatCard(&data.sPlayer, &data.sOptions);
	}

	if (error == eCartridgeError::DataCorrupt)
	{
		Log("One or more saved games were corrupted and had to be reset");
		error = eCartridgeError::None;
	}

	if (error == eCartridgeError::FilesystemCorrupt)
	{
		Log("File system became corrupted - system hungup");
		pSystem->HangUp();
		return false;
	}

	if (error == eCartridgeError::None)
	{
		Log("Save data CRC ok.");
		// Do your initial loading here.
		return true;
	}

	return false;
}

