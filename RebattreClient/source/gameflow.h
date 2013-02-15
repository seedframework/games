#ifndef _GAMEFLOW_H_
#define _GAMEFLOW_H_

#include <api/rocket/RocketInterface.h>
#include <Rocket/Core.h>
#include <Seed.h>

#include "states/splash_state.h"
#include "states/main_menu_state.h"
#include "states/options_state.h"
#include "states/credits_state.h"
#include "states/game_state.h"
#include "data/game_data.h"

using namespace Seed;
using namespace Seed::RocketGui;

class GameFlow;
extern GameFlow *gFlow;
extern GameData *gGameData;

class GameFlow : public IGameApp,
			public IEventSystemListener,
			public IEventInputKeyboardListener,
			public IEventPresentationListener,
			public IRocketEventListener
{
	public:
		GameFlow();
		virtual ~GameFlow();

		virtual bool Initialize();
		virtual bool Update(f32 dt);
		virtual bool Shutdown();

		// GUI
		bool LoadGUI(const String &doc);
		bool ReloadGUI();
		bool UnloadGUI();
		bool InitializeGUI();
		void ReleaseGUI();

		const u32 GetLeftPlayerPoints();
		void SetLeftPlayerPoints(const u32 points);

		const u32 GetRightPlayerPoints();
		void SetRightPlayerPoints(const u32 points);

		// IEventSystemListener
		virtual void OnSystemShutdown(const EventSystem *ev);

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardRelease(const EventInputKeyboard *ev);

		// IEventPresentationListener
		virtual void OnPresentationLoaded(const EventPresentation *ev);

		// IRocketEventListener
		virtual void OnGuiEvent(Rocket::Core::Event &ev, const Rocket::Core::String &script);

		inline Camera *GetCamera() const;
		inline SceneNode *GetScene() const;

		void LoadSceneFile(const String &file);
		const String &GetSceneFile() const;
		void DoLoad();

		void Menu();

	private:
		bool SaveSystemFlow() const;

	private:
		SEED_DISABLE_COPY(GameFlow);

		SceneNode			*pScene;
		Camera				*pCamera;
		Presentation		cPres;
		String				sDocument;

		// State Machine
		StateMachine		cFlow;

		// State Machine states
		SplashState			cSplash;
		MainMenuState		cMenu;
		OptionsState		cOptions;
		CreditsState		cCredits;
		GameState			cGame;
		StateMachineState	cLoad;

		// State Machine Events
		StateMachineEvent	cOnSplash;
		StateMachineEvent	cOnMenu;
		StateMachineEvent	cOnOptions;
		StateMachineEvent	cOnCredits;
		StateMachineEvent	cOnGame;
		StateMachineEvent	cOnLoad;

		// State Machine transitions
		StateMachineTransition cSplashToMenu;
		StateMachineTransition cMenuToGame;
		StateMachineTransition cMenuToOptions;
		StateMachineTransition cMenuToCredits;
		StateMachineTransition cOptionsToMenu;
		StateMachineTransition cCreditsToMenu;
		StateMachineTransition cGameToMenu;
		StateMachineTransition cGameToLoad;
		StateMachineTransition cLoadToGame;

		Image	*pSplashImg;

		// GUI
		RocketInterface					*pRocket;
		Rocket::Core::Context			*pContext;
		Rocket::Core::ElementDocument	*pDoc;

		// GUI Elements
		Rocket::Core::Element	*pElementLeftPlayerPoints;
		Rocket::Core::Element	*pElementRightPlayerPoints;
		Rocket::Core::Element	*pElementSfx;
		Rocket::Core::Element	*pElementBgm;

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
