#include "gui_manager.h"
#include "../scene/game_scene.h"
#include "../gameflow.h"
#include "api/net/Address.h"
#include <Rocket/Debugger.h>
#include <Rocket/Controls.h>

GuiManager *gGui = nullptr;

GuiManager::GuiManager()
	: pRocket(nullptr)
	, pContext(nullptr)
	, pDoc(nullptr)
{
	gGui = this;
}

GuiManager::~GuiManager()
{
	gGui = nullptr;
}

bool GuiManager::Initialize()
{
	pScreen->EnableCursor(true);
	return this->InitializeGUI();
}

bool GuiManager::Shutdown()
{
	RocketEventManager::RemoveListener(this);
	this->ReleaseGUI();
	return true;
}

bool GuiManager::UnloadGUI()
{
	Log("Unloading GUI Document");
	if (pDoc)
	{
		pDoc->Hide();
		pContext->UnloadDocument(pDoc);
		pDoc->RemoveReference();
		pDoc = nullptr;
	}

	return true;
}

bool GuiManager::ReloadGUI()
{
	return this->LoadGUI(sDocument);
}

bool GuiManager::LoadGUI(const String &doc)
{
	if (this->UnloadGUI())
	{
		Log("Loading GUI Document");
		pDoc = pContext->LoadDocument(doc.c_str());
		if (pDoc != nullptr)
		{
			Rocket::Core::Element *title = pDoc->GetElementById("title");
			if (title != nullptr)
				title->SetInnerRML(pDoc->GetTitle());

			pDoc->Focus();
			pDoc->Show();

			if (pDoc->GetElementById("leftPlayerPoints") != nullptr)
				pElementLeftPlayerPoints = pDoc->GetElementById("leftPlayerPoints");

			if (pDoc->GetElementById("sfx") != nullptr && gGameData->IsSfxEnabled())
				pDoc->GetElementById("sfx")->SetAttribute("checked", "");

			if (pDoc->GetElementById("bgm") != nullptr && gGameData->IsBgmEnabled())
				pDoc->GetElementById("bgm")->SetAttribute("checked", "");
		}

		sDocument = doc;
	}

	return true;
}

bool GuiManager::InitializeGUI()
{
	pRocket = sdNew(RocketInterface());
	pRocket->sName = "GUI";
	Rocket::Core::SetRenderInterface(pRocket);
	Rocket::Core::SetFileInterface(pRocket);
	Rocket::Core::SetSystemInterface(pRocket);
	Rocket::Core::Initialise();
	Rocket::Controls::Initialise();

	pContext = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(pScreen->GetWidth(), pScreen->GetHeight()));
	if (pContext == nullptr)
	{
		Rocket::Core::Shutdown();
		return false;
	}

	Rocket::Core::String fonts[4];
	fonts[0] = "fonts/Delicious-Roman.otf";
	fonts[1] = "fonts/Delicious-Italic.otf";
	fonts[2] = "fonts/Delicious-Bold.otf";
	fonts[3] = "fonts/Delicious-BoldItalic.otf";

	for (unsigned int i = 0; i < sizeof(fonts) / sizeof(Rocket::Core::String); i++)
		Rocket::Core::FontDatabase::LoadFontFace(fonts[i]);

	Rocket::Debugger::Initialise(pContext);
	pRocket->SetCurrentContext(pContext);
	pInput->AddKeyboardListener(pRocket);
	pInput->AddPointerListener(pRocket);
	pRocket->SetZ(-1000.0f);

	RocketEventManager::AddListener(this);
	return true;
}

void GuiManager::ReleaseGUI()
{
	RocketEventManager::RemoveListener(this);

	pInput->RemovePointerListener(pRocket);
	pInput->RemoveKeyboardListener(pRocket);

	pContext->UnloadAllDocuments();

	if (pDoc)
	{
		pDoc->RemoveReference();
		pDoc = nullptr;
	}

	pContext->RemoveReference();

	Rocket::Core::Shutdown();
	sdDelete(pRocket);
}

void GuiManager::OnGuiEvent(Rocket::Core::Event &ev, const Rocket::Core::String &script)
{
	UNUSED(ev);
	Rocket::Core::StringList commands;
	Rocket::Core::StringUtilities::ExpandString(commands, script, ';');
	for (size_t i = 0; i < commands.size(); ++i)
	{
		Rocket::Core::StringList values;
		Rocket::Core::StringUtilities::ExpandString(values, commands[i], ' ');
		if (values.empty())
			return;

		if (values[0] == "goto" && values.size() > 1)
		{
			if (values[1] == "credits")
				gFlow->Credits();
			else if (values[1] == "menu")
				gFlow->Menu();
			else if (values[1] == "options")
				gFlow->Options();
			else if (values[1] == "game")
			{
				//pRSClient->iIDPlayer = RSClient::PlayerOne;
				//pRSClient->iIDPlayer = RSClient::PlayerTwo;
				gFlow->DoLoad("game.scene");

			}
		}
		else if (values[0] == "exit")
		{
			pSystem->Shutdown();
		}
		else if (values[0] == "toggle" && values.size() > 1)
		{
			if (values[1] == "sfx")
			{
				if (gGameData->IsSfxEnabled())
				{
					gGameData->SetSfxVolume(pSoundSystem->GetSfxVolume());
					pSoundSystem->SetSfxVolume(0.0f);
					gGameData->SetSfxEnabled(false);
				}
				else
				{
					pSoundSystem->SetSfxVolume(gGameData->GetSfxVolume());
					gGameData->SetSfxEnabled(true);
				}
			}
			else if (values[1] == "bgm")
			{
				if (gGameData->IsBgmEnabled())
				{
					gGameData->SetBgmVolume(pSoundSystem->GetMusicVolume());
					pSoundSystem->SetMusicVolume(0.0f);
					gGameData->SetBgmEnabled(false);
				}
				else
				{
					pSoundSystem->SetMusicVolume(gGameData->GetBgmVolume());
					gGameData->SetBgmEnabled(true);
				}
			}
			else if (values[1] == "fullscreen")
			{
				//this->ReleaseGUI();

				if (gGameData->IsFullScreenEnabled())
				{
					gGameData->SetFullScreenEnabled(false);
					pScreen->ToggleFullscreen();
					//pSystem->Shutdown();
				}
				else
				{
					gGameData->SetFullScreenEnabled(true);
					pScreen->ToggleFullscreen();
					//pSystem->Shutdown();
				}

				//this->InitializeGUI();
				//this->ReloadGUI();
			}
		}
	}
}

// GUI Elements
u32 GuiManager::GetLeftPlayerPoints() const
{
	return gGameData->GetLeftPlayerPoints();
}

void GuiManager::SetLeftPlayerPoints(u32 points)
{
	char x[100];
	snprintf(x, 100, "%d", points);
	pElementLeftPlayerPoints->SetInnerRML(Rocket::Core::String(x));
	gGameData->SetLeftPlayerPoints(points);
}

ISceneObject *GuiManager::GetSceneObject() const
{
	return pRocket;
}
