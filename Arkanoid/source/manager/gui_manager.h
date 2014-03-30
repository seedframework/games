#ifndef _GUI_MANAGER_H
#define _GUI_MANAGER_H

#include "Defines.h"
#include <api/rocket/RocketInterface.h>
#include <Rocket/Core.h>

using namespace Seed;
using namespace Seed::RocketGui;

class GuiManager;
extern GuiManager *gGui;

class GuiManager : public IRocketEventListener
{
	SEED_DISABLE_COPY(GuiManager)

	public:
		GuiManager();
		virtual ~GuiManager();

		bool Initialize();
		bool Shutdown();

		ISceneObject *GetSceneObject() const;

		// GUI
		bool LoadGUI(const String &doc);
		bool ReloadGUI();
		bool UnloadGUI();
		void ReleaseGUI();

		u32 GetLeftPlayerPoints() const;
		void SetLeftPlayerPoints(const u32 points);

		// IRocketEventListener
		virtual void OnGuiEvent(Rocket::Core::Event &ev, const Rocket::Core::String &script);

	private:
		bool InitializeGUI();

	private:
		String				sDocument;

		// GUI
		RocketInterface					*pRocket;
		Rocket::Core::Context			*pContext;
		Rocket::Core::ElementDocument	*pDoc;

		// GUI Elements
		Rocket::Core::Element	*pElementLeftPlayerPoints;
};

#endif // _GUI_MANAGER_H
