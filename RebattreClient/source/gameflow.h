#ifndef _GAMEFLOW_H_
#define _GAMEFLOW_H_

#include "defines.h"
#include "states/splash_state.h"
#include "states/main_menu_state.h"
#include "states/options_state.h"
#include "states/credits_state.h"
#include "states/lobby_state.h"
#include "states/game_state.h"
#include "data/game_data.h"

using namespace Seed;

class GameFlow;
extern GameFlow *gFlow;
extern GameData *gGameData;

class GameFlow : public IGameApp,
			public IEventSystemListener,
			public IEventInputKeyboardListener
{
	SEED_DISABLE_COPY(GameFlow)

	public:
		GameFlow();
		virtual ~GameFlow();

		inline Camera *GetCamera() const;
		inline SceneNode *GetScene() const;

		void LoadSceneFile(const String &file);
		const String &GetSceneFile() const;

		void DoLoad(const String &scene = "");
		void Menu();
		void Credits();
		void Options();
		void Lobby();

		virtual bool Initialize();
		virtual bool Update(f32 dt);
		virtual bool Shutdown();

		// IEventSystemListener
		virtual void OnSystemShutdown(const EventSystem *ev);

		// IEventInputKeyboardListener
		virtual bool OnInputKeyboardRelease(const EventInputKeyboard *ev);

		// IEventInputKeyboardListener
		virtual bool OnInputKeyboardPress(const EventInputKeyboard *ev);

	private:
		bool SaveSystemFlow() const;

	private:
		SceneNode			*pScene;
		Camera				*pCamera;
		Presentation		cPres;

		// State Machine
		StateMachine		cFlow;

		// State Machine states
		SplashState			cSplash;
		MainMenuState		cMenu;
		OptionsState		cOptions;
		CreditsState		cCredits;
		LobbyState			cLobby;
		GameState			cGame;
		StateMachineState	cLoad;

		// State Machine Events
		StateMachineEvent	cOnSplash;
		StateMachineEvent	cOnMenu;
		StateMachineEvent	cOnOptions;
		StateMachineEvent	cOnCredits;
		StateMachineEvent	cOnLobby;
		StateMachineEvent	cOnGame;
		StateMachineEvent	cOnLoad;

		// State Machine transitions
		StateMachineTransition cSplashToMenu;
		StateMachineTransition cMenuToLobby;
		StateMachineTransition cMenuToOptions;
		StateMachineTransition cMenuToCredits;
		StateMachineTransition cOptionsToMenu;
		StateMachineTransition cLobbyToMenu;
		StateMachineTransition cLobbyToGame;
		StateMachineTransition cCreditsToMenu;
		StateMachineTransition cGameToMenu;
		StateMachineTransition cGameToLoad;
		StateMachineTransition cLoadToGame;

		Image	*pSplashImg;
		String	sSceneFile;
};

inline Camera *GameFlow::GetCamera() const
{
	return pCamera;
}

inline SceneNode *GameFlow::GetScene() const
{
	return pScene;
}

#endif // _GAMEFLOW_H_
