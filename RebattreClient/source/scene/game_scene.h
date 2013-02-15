#ifndef _GAME_H_
#define _GAME_H_

#include <api/rocket/RocketInterface.h>

#include "../defines.h"
#include "../states/game_pause_state.h"
#include "../states/gameover_state.h"
#include "../states/game_run_state.h"
#include "../controller/camera_controller.h"
#include "../controller/world_controller.h"
#include "../controller/sound_controller.h"
#include "../entity/player_left_entity.h"
#include "../entity/player_right_entity.h"

using namespace Seed::RocketGui;

class GameScene;

extern SceneNode *gScene;
extern PhysicsManager *gPhysicsManager;
extern SoundController *gSoundController;
extern WorldController *gWorldController;
extern GameScene *gGameScene;

class GameScene : public IEventInputKeyboardListener,
				  public IEventJobListener,
				  public IRocketEventListener
{
	public:
		GameScene(SceneNode *parent, Camera *mainCamera, const String &sceneFile);
		virtual ~GameScene();

		virtual bool Initialize();
		virtual bool Update(f32 dt);
		virtual bool Shutdown();

		void Pause();
		void Resume();

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardRelease(const EventInputKeyboard *ev);

		// IEventJobListener
		virtual void OnJobCompleted(const EventJob *ev);
		virtual void OnJobAborted(const EventJob *ev);

		// IRocketEventListener
		virtual void OnGuiEvent(Rocket::Core::Event &ev, const Rocket::Core::String &script);

		// Load
		virtual void LoadMapColliders();

	private:
		SEED_DISABLE_COPY(GameScene);

		PlayerLeftEntity	*pPlayerLeft;
		PlayerRightEntity	*pPlayerRight;
		Camera				*pCamera;
		CameraController	clCamera;
		SceneNode			*pParentScene;
		SceneNode			cScene;
		Music				musTheme;
		GameMap				*pGameMap;
		bool				bPaused;
		bool				bInitialized;

		WorldController	cWorldController;
		PhysicsManager	cPhysicsManager;
		SoundController	cSoundController;

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

		bool	fChangeLevel;

		Image *pGameOverImg;

};

#endif // _GAMEFLOW_H_
