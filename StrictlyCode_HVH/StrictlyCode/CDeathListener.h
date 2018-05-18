#include <Windows.h>
#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"
#include "EntityStructs.h"
#include "OptionsManager.h"
#include "Globals.h"
#include "Utilities.h"
#include "CNotify.h"
#include <vector>
#pragma comment(lib, "Winmm.lib")

void SayChat(const char *text)
{
	char buffer[420];
	sprintf_s(buffer, "say \"%s\"", text);
	NSDK::I::Engine()->ClientCmd_Unrestricted(buffer);
}

class CDeathListener
{
	class DeathListener : public IGameEventListener2
	{
	public:
		void start()
		{
			if (!NSDK::I::GameEvents()->AddListener(this, "player_death", false))
			{
				NSDK::I::CVar()->ConsoleColorPrintf(NSDK::Color(255, 0, 0), ("-> Failed Death Listener. \n"));
			}
		}
		void stop()
		{
			NSDK::I::GameEvents()->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent* event) override
		{
			CDeathListener::singleton()->OnFireEvent(event);
		}
		int GetEventDebugID(void) override
		{
			return EVENT_DEBUG_ID_INIT /*0x2A*/;
		}
	};
public:
	static CDeathListener* singleton()
	{
		static CDeathListener* instance = new CDeathListener;
		return instance;
	}

	void init()
	{
		_listener.start();
	}

	void OnFireEvent(IGameEvent* event)
	{
		if (!strcmp(event->GetName(), "player_death"))
		{
			int attacker = event->GetInt("attacker");
			int dead = event->GetInt("userid");
			std::string w_name = event->GetString("weapon");
			CBaseEntity* pEntity = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(NSDK::I::Engine()->GetPlayerUserID(dead));
			CBaseEntity* g_Local = CBaseEntity::GetLocalPlayer();
			if (!pEntity) return;

			if (!g_Local) return;

			if (NSDK::I::Engine()->GetPlayerUserID(attacker) == NSDK::I::Engine()->GetLocalPlayer() && NSDK::I::Engine()->GetPlayerUserID(dead) != NSDK::I::Engine()->GetLocalPlayer())
			{
				if (Options.bTrashTalk)
				{

					if (rand() % 4 >= 2 && !info::should_baim[pEntity->EntIndex()] && w_name != "knife" && w_name != "taser")
					{
						event->SetInt("headshot", 1);
					}

					const static std::vector<std::string> kill_says =
					{
						"cy@ ur head",
						"ez taps",
						"cy@ nn",
						"rekt by superior hack",
						"refund ur cheat l0l",
						"thats a dead",
						"1tabb (dro$ed)"
					};

					SayChat(kill_says.at(rand() % kill_says.size()).c_str());
				}
			}

			if (NSDK::I::Engine()->GetPlayerUserID(dead) == NSDK::I::Engine()->GetLocalPlayer() && NSDK::I::Engine()->GetPlayerUserID(attacker) != NSDK::I::Engine()->GetLocalPlayer())
			{
				if (Options.bTrashTalk)
				{

					const static std::vector<std::string> death_says =
					{
					"serverside retard",
					"1way retard",
					"nice p2c retard",
					"nice baim retard",
					"nice p2paste retard",
					"ragetap"
					};

					SayChat(death_says.at(rand() % death_says.size()).c_str());
				}
			}

		}
	}
private:
	DeathListener _listener;
};