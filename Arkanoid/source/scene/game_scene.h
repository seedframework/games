#ifndef _GAME_H_
#define _GAME_H_

#include <api/rocket/RocketInterface.h>

#include "../defines.h"
#include "../states/game/game_pause_state.h"
#include "../states/gameover_state.h"
#include "../states/game/game_run_state.h"
#include "../manager/camera_manager.h"
#include "../manager/physics_manager.h"
#include "../manager/world_manager.h"
#include "../manager/sound_manager.h"
#include "../entity/player_entity.h"
#include "../entity/block_entity.h"

using namespace Seed::RocketGui;

class GameScene;

extern SceneNode *gScene;
extern PhysicsManager *gPhysicsManager;
extern SoundManager *gSoundManager;
extern WorldManager *gWorldManager;
extern GameScene *gGameScene;

class GameScene : public IEventInputKeyboardListener,
				  public IRocketEventListener
{
	SEED_DISABLE_COPY(GameScene)

	public:
		GameScene(SceneNode *parent, Camera *mainCamera, const String &sceneFile);
		virtual ~GameScene();

		virtual bool Initialize();
		virtual bool Update(f32 dt);
		virtual bool Shutdown();

		void Pause();
		void Resume();

		// IEventInputKeyboardListener
		virtual bool OnInputKeyboardRelease(const EventInputKeyboard *ev);

		// IEventInputKeyboardListener
		virtual bool OnInputKeyboardPress(const EventInputKeyboard *ev);

		// IRocketEventListener
		virtual void OnGuiEvent(Rocket::Core::Event &ev, const Rocket::Core::String &script);

		// Load
		virtual void LoadMapColliders();


	private:
		PlayerEntity		*pPlayerLeft;
		Camera				*pCamera;
		CameraManager		cCamera;
		SceneNode			*pParentScene;
		SceneNode			cScene;
		Music				musTheme;
		GameMap				*pGameMap;
		bool				bPaused;
		bool				bInitialized;

		WorldManager	cWorldManager;
		PhysicsManager	cPhysicsManager;
		SoundManager	cSoundManager;

		// State Machine
		StateMachine		cFlow;

		// State Machine State
		GameRunState		cRun;
		GamePauseState		cPause;
		GameOverState		cGameOver;
		StateMachineState	cMenu;

		// State Machine Event
		StateMachineEvent	cOnPause;
		StateMachineEvent	cOnRun;
		StateMachineEvent	cOnMenu;
		StateMachineEvent	cOnGameOver;

		// State Machine Transition
		StateMachineTransition cRunToPause;
		StateMachineTransition cPauseToRun;
		StateMachineTransition cPauseToMenu;
		StateMachineTransition cRunToGameOver;
		StateMachineTransition cGameOverToMenu;

		String sSceneFile;
		Image *pGameOverImg;
};

#endif // _GAMEFLOW_H_
