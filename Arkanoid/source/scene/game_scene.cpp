#include "game_scene.h"
#include "../gameflow.h"
#include "../manager/gui_manager.h"

SceneNode *gScene = NULL;
PhysicsManager *gPhysicsManager = NULL;
SoundManager *gSoundManager =NULL;
WorldManager *gWorldManager = NULL;
GameScene *gGameScene = NULL;

GameScene::GameScene(SceneNode *parent, Camera *mainCamera, const String &sceneFile)
	: pPlayerLeft(NULL)
	, pCamera(mainCamera)
	, cCamera()
	, pParentScene(parent)
	, musTheme()
	, bPaused(false)
	, bInitialized(false)
	, sSceneFile(sceneFile)
	, fChangeLevel(false)
{
	gScene = &cScene;
	gPhysicsManager = &cPhysicsManager;
	gSoundManager = &cSoundManager;
	gWorldManager = &cWorldManager;
	gGameScene = this;
}

GameScene::~GameScene()
{
	gScene = NULL;
}

bool GameScene::Initialize()
{
	pParentScene->Add(&cScene);

	// Create the transitions
	cRunToPause.Initialize(&cRun, &cOnPause, &cPause);
	cPauseToRun.Initialize(&cPause, &cOnRun, &cRun);
	cPauseToMenu.Initialize(&cPause, &cOnMenu, &cMenu);
	cRunToGameOver.Initialize(&cRun, &cOnGameOver, &cGameOver);
	cGameOverToMenu.Initialize(&cGameOver, &cOnMenu, &cMenu);

	// Create the State Machine.
	cFlow.RegisterTransition(&cRunToPause);
	cFlow.RegisterTransition(&cPauseToRun);
	cFlow.RegisterTransition(&cPauseToMenu);
	cFlow.RegisterTransition(&cRunToGameOver);
	cFlow.RegisterTransition(&cGameOverToMenu);

	cFlow.Initialize(&cRun);

	auto cb = [&](Job *self)
	{
		auto job = static_cast<FileLoader *>(self);

		if(job->GetState() == eJobState::Completed)
		{
			Reader r(job->pFile);
			cScene.Load(r);
			Log("Scene Name: %s len %d", cScene.sName.c_str(), cScene.Size());
			sdDelete(job);

			// Validate the music to play
			if (gGameData->IsBgmEnabled() == true)
			{
				musTheme.Load("sounds/gameplay_music.ogg");
				musTheme.SetVolume(1.0f);
				pSoundSystem->PlayMusic(&musTheme);
			}

			SceneNode *sprites = (SceneNode *)cScene.GetChildByName("Sprites");
			pGameMap = (GameMap *)cScene.GetChildByName("Map");

			MapLayerMetadata *game = pGameMap->GetLayerByName("Game")->AsMetadata();
			game->SetVisible(false);

			for (unsigned i = 0, len = game->Size(); i < len; ++i)
			{
				MetadataObject *placeHolder = static_cast<MetadataObject *>(game->GetChildAt(i));
				//const String &type = placeHolder->GetProperty("Type");
				//if (type == "Entity")
				{
					Entity* entity = cWorldManager.BuildEntity(*placeHolder, sprites);

					if (entity->GetName() == "PlayerLeft")
					{
						pPlayerLeft = static_cast<PlayerEntity*>(entity);
					}
				}
			}

			this->LoadMapColliders();
			cCamera.SetCamera(pCamera);

			MapLayerTiled *bg = pGameMap->GetLayerByName("Background")->AsTiled();

			f32 hw = bg->GetWidth() * 0.5f;
			f32 hh = bg->GetHeight() * 0.5f;
			cCamera.SetArea(Rect4f(-hw, -hh, bg->GetWidth(), bg->GetHeight()));

			sprites->SetVisible(false);

			pGameOverImg = (Image *)cScene.GetChildByName("GameOverImage");
			pGameOverImg->SetVisible(false);

			bInitialized = true;
		}
		else if(job->GetState() == eJobState::Aborted)
		{
			// ...
		}
	};

	String f("scenes/");
	pJobManager->Add(sdNew(FileLoader(f + sSceneFile, cb)));

	RocketEventManager::AddListener(this);
	pInput->AddKeyboardListener(this);

	// Get the initial points from game data
	gGui->SetLeftPlayerPoints(gGameData->GetLeftPlayerPoints());

	return true;
}

bool GameScene::Update(f32 dt)
{
	if (!bInitialized)
		return true;

	cFlow.Update(dt);
	if (!bPaused)
	{
		cPhysicsManager.Update(dt);
		cWorldManager.Update(dt);
	}

	if(gGameData->GetLeftPlayerPoints() == 5)
	{
		pPlayerLeft->GetSprite()->SetVisible(false);

		pGameOverImg->SetVisible(true);
		pGameOverImg->SetPosition(pCamera->GetPosition() - Vector3f(-400.0f, -300.0f, 0.0f));
		cFlow.OnEvent(&cOnGameOver, this);

		gGameData->SetLeftPlayerPoints(0);
	}

	return true;
}

bool GameScene::Shutdown()
{
	musTheme.Unload();

	cWorldManager.Clear();

	pParentScene->Remove(&cScene);
	cScene.Unload();
	pParentScene = NULL;

	pInput->RemoveKeyboardListener(this);
	RocketEventManager::RemoveListener(this);

	return true;
}

void GameScene::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();
	if (k == eKey::Escape)
	{
		if (bPaused)
			cFlow.OnEvent(&cOnRun, this);
		else
			cFlow.OnEvent(&cOnPause, this);
	}
}

void GameScene::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	UNUSED(ev);
}

void GameScene::LoadMapColliders()
{
	MapLayerMetadata *game = pGameMap->GetLayerByName("Colliders")->AsMetadata();
	game->SetVisible(false);
	for (unsigned i = 0, len = game->Size(); i < len; ++i)
	{
		MetadataObject *placeHolder = static_cast<MetadataObject *>(game->GetChildAt(i));

		cPhysicsManager.CreateStaticBody(placeHolder);
	}
}

void GameScene::OnGuiEvent(Rocket::Core::Event &ev, const Rocket::Core::String &script)
{
	UNUSED(ev)
	if (script == "resume")
	{
		cFlow.OnEvent(&cOnRun, this);
	}
	if (script == "quit")
	{
		cFlow.OnEvent(&cOnMenu);
		gFlow->Menu();
	}
}

void GameScene::Pause()
{
	bPaused = true;
}

void GameScene::Resume()
{
	bPaused = false;
}

