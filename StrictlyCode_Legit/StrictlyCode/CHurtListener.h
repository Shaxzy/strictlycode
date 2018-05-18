#include <Windows.h>
#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"
#include "EntityStructs.h"
#include "OptionsManager.h"
#include "Utilities.h"
#include "CNotify.h"
#pragma comment(lib, "Winmm.lib")

class CHurtListener
{
	class HurtListener : public IGameEventListener2
	{
	public:
		void start()
		{
			if (!NSDK::I::GameEvents()->AddListener(this, "player_hurt", false))
			{
				NSDK::I::CVar()->ConsoleColorPrintf(NSDK::Color(255, 0, 0), ("-> Failed hurt_listener. \n"));
			}
			if (NSDK::I::GameEvents()->AddListener(this, "player_hurt", false))
			{
			}
		}
		void stop()
		{
			NSDK::I::GameEvents()->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent* event) override
		{
			CHurtListener::singleton()->OnFireEvent(event);
		}
		int GetEventDebugID(void) override
		{
			return EVENT_DEBUG_ID_INIT /*0x2A*/;
		}
	};
public:
	static CHurtListener* singleton()
	{
		static CHurtListener* instance = new CHurtListener;
		return instance;
	}

	void init()
	{
		_listener.start();
	}

	void OnFireEvent(IGameEvent* event)
	{
		if (!strcmp(event->GetName(), "player_hurt"))
		{
			int attacker = event->GetInt("attacker");
			int playerid = event->GetInt("userid");
			int damage = event->GetInt("dmg_health");
			int hitgroup = event->GetInt("hitgroup");

			CBaseEntity* pEntity = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(NSDK::I::Engine()->GetPlayerUserID(playerid));
			NSDK::PlayerInfo entityInfos;
			NSDK::I::Engine()->GetPlayerInfo(pEntity->EntIndex(), &entityInfos);
			if (NSDK::I::Engine()->GetPlayerUserID(attacker) == NSDK::I::Engine()->GetLocalPlayer())
			{
				_flHurtTime = NSDK::I::GlobalVars()->curtime;
				auto curtime = NSDK::I::GlobalVars()->curtime;
				if (_flHurtTime + 0.25f >= curtime) NSDK::I::Engine()->ClientCmd_Unrestricted("play buttons\\arena_switch_press_02.wav");
			}
		}
	}

	/* ~~ Mark's Sexy Hitmarkers ~~ */

	void OnPaint()
	{
		if (!NSDK::I::Engine()->isConnected() || !NSDK::I::Engine()->isInGame()) return;
		auto curtime = NSDK::I::GlobalVars()->curtime;
		auto lineSize = 8;

		if (_flHurtTime + 0.25f >= curtime)
		{
			int screenSizeX, screenCenterX;
			int screenSizeY, screenCenterY;

			NSDK::I::Engine()->GetScreenSize(screenSizeX, screenSizeY);

			screenCenterX = screenSizeX / 2;
			screenCenterY = screenSizeY / 2;

			NSDK::I::MatSurface()->DrawSetColor(NSDK::Color(255, 153, 51, 255));
			NSDK::I::MatSurface()->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4));
			NSDK::I::MatSurface()->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4));
			NSDK::I::MatSurface()->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4));
			NSDK::I::MatSurface()->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4));
		}
	}

private:
	HurtListener _listener;
	float        _flHurtTime;
};