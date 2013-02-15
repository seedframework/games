#include "game_scene.h"
#include "../gameflow.h"
#include "../controller/world_controller.h"
#include <SceneNode.h>

SceneNode *gScene = NULL;
PhysicsManager *gPhysicsManager = NULL;
SoundController *gSoundController =NULL;
WorldController *gWorldController = NULL;
GameScene *gGameScene = NULL;

enum
{
	kJobLoadScene
};

GameScene::GameScene(SceneNode *parent, Camera *mainCamera, const String &sceneFile)
	: pPlayerLeft(NULL)
	, pPlayerRight(NULL)
	, pCamera(mainCamera)
	, clCamera()
	, pParentScene(parent)
	, musTheme()
	, bPaused(false)
	, bInitialized(false)
	, sSceneFile(sceneFile)
	, fChangeLevel(false)
{
	gScene = &cScene;
	gPhysicsManager = &cPhysicsManager;
	gSoundController = &cSoundController;
	gWorldController = &cWorldController;
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

	RocketEventManager::AddListener(this);
	pInput->AddKeyboardListener(this);

	String f("scenes/");
	pJobManager->Add(New(FileLoader(f + sSceneFile, kJobLoadScene, this)));

	// Get the initial points from game data
	gFlow->SetLeftPlayerPoints(gGameData->GetLeftPlayerPoints());
	gFlow->SetRightPlayerPoints(gGameData->GetRightPlayerPoints());

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
		cWorldController.Update(dt);
	}

	if(gGameData->GetLeftPlayerPoints() == 5)
	{
		pPlayerLeft->GetSprite()->SetVisible(false);
		pPlayerRight->GetSprite()->SetVisible(false);

		pGameOverImg->SetVisible(true);
		pGameOverImg->SetPosition(pCamera->GetPosition() - Vector3f(-400.0f, -300.0f, 0.0f));
		cFlow.OnEvent(&cOnGameOver, this);

		gGameData->SetLeftPlayerPoints(0);
		gGameData->SetRightPlayerPoints(0);
	}

	if(gGameData->GetRightPlayerPoints() == 5)
	{
		pPlayerLeft->GetSprite()->SetVisible(false);
		pPlayerRight->GetSprite()->SetVisible(false);

		pGameOverImg->SetVisible(true);
		pGameOverImg->SetPosition(pCamera->GetPosition() - Vector3f(-400.0f, -300.0f, 0.0f));
		cFlow.OnEvent(&cOnGameOver, this);

		gGameData->SetLeftPlayerPoints(0);
		gGameData->SetRightPlayerPoints(0);
	}

	return true;
}

bool GameScene::Shutdown()
{
	musTheme.Unload();

	cWorldController.Clear();

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
	if (k == Seed::KeyEscape)
	{
		if (bPaused)
			cFlow.OnEvent(&cOnRun, this);
		else
			cFlow.OnEvent(&cOnPause, this);
	}
}

void GameScene::OnJobCompleted(const EventJob *ev)
{
	switch (ev->GetName())
	{
		case kJobLoadScene:
		{
			FileLoader *job = (FileLoader *)ev->GetJob();
			Reader r(job->pFile);
			cScene.Load(r);
			Log("Scene Name: %s len %d", cScene.sName.c_str(), cScene.Size());
			Delete(job);

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
			//game->SetVisible(false);

			for (unsigned i = 0, len = game->Size(); i < len; ++i)
			{
				IMetadataObject *placeHolder = static_cast<IMetadataObject *>(game->GetChildAt(i));
				//const String &type = placeHolder->GetProperty("Type");
				//if (type == "Entity")
				{
					Entity* entity = cWorldController.BuildEntity(*placeHolder, sprites);
					//Log("%s", entity->GetName().c_str());
					if (entity->GetClassName() == "PlayerLeft")
					{
						pPlayerLeft = static_cast<PlayerLeftEntity*>(entity);
					}
					if (entity->GetClassName() == "PlayerRight")
					{
						pPlayerRight = static_cast<PlayerRightEntity*>(entity);
					}
				}
			}

			this->LoadMapColliders();

			clCamera.SetCamera(pCamera);

			MapLayerTiled *bg = pGameMap->GetLayerByName("Background")->AsTiled();

			f32 hw = bg->GetWidth() * 0.5f;
			f32 hh = bg->GetHeight() * 0.5f;
			clCamera.SetArea(Rect4f(-hw, -hh, bg->GetWidth(), bg->GetHeight()));

			sprites->SetVisible(false);

			pGameOverImg = (Image *)cScene.GetChildByName("GameOverImage");
			pGameOverImg->SetVisible(false);

			bInitialized = true;
		}
		break;
	}
}

void GameScene::OnJobAborted(const EventJob *ev)
{
	Job *job = ev->GetJob();
	Delete(job);
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

void GameScene::LoadMapColliders()
{
	MapLayerMetadata *game = pGameMap->GetLayerByName("Colliders")->AsMetadata();
	game->SetVisible(false);
	for (unsigned i = 0, len = game->Size(); i < len; ++i)
	{
		IMetadataObject *placeHolder = static_cast<IMetadataObject *>(game->GetChildAt(i));

		cPhysicsManager.CreateStaticBody(placeHolder);
	}
}
