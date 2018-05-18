#include <Windows.h>
#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"
#include "EntityStructs.h"
#include "OptionsManager.h"
#include "Globals.h"
#include "Utilities.h"
#include "CNotify.h"
#pragma comment(lib, "Winmm.lib")

class CFireListener
{
	class FireListener : public IGameEventListener2
	{
	public:
		void start()
		{
			if (!NSDK::I::GameEvents()->AddListener(this, "weapon_fire", false))
			{
				NSDK::I::CVar()->ConsoleColorPrintf(NSDK::Color(255, 0, 0), ("-> Failed Weapon Fire Listener. \n"));
			}
		}
		void stop()
		{
			NSDK::I::GameEvents()->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent* event) override
		{
			CFireListener::singleton()->OnFireEvent(event);
		}
		int GetEventDebugID(void) override
		{
			return EVENT_DEBUG_ID_INIT /*0x2A*/;
		}
	};
public:
	static CFireListener* singleton()
	{
		static CFireListener* instance = new CFireListener;
		return instance;
	}

	void init()
	{
		_listener.start();
	}

	void OnFireEvent(IGameEvent* event)
	{
		if (!strcmp(event->GetName(), "weapon_fire"))
		{
			int firing_player = event->GetInt("userid");
			CBaseEntity* g_Local = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(NSDK::I::Engine()->GetPlayerUserID(firing_player));

			if (NSDK::I::Engine()->GetPlayerUserID(firing_player) == NSDK::I::Engine()->GetLocalPlayer())
			{
				if (!Backtracking::tick_is_valid[Local::cur_target])
				{
					info::shots[Local::cur_target]++;
					info::shot_fired[Local::cur_target] = true;
				}
			}
		}

	}

private:
	FireListener _listener;
};