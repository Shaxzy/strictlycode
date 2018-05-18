#include <Windows.h>
#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"
#include "EntityStructs.h"
#include "OptionsManager.h"
#include "Globals.h"
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
				NSDK::I::CVar()->ConsoleColorPrintf(NSDK::Color(255, 0, 0), ("-> Failed Hurt Listener. \n"));
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
			int hpleft = event->GetInt("health");
			CBaseEntity* pEntity = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(NSDK::I::Engine()->GetPlayerUserID(playerid));

			if (!pEntity) return;

			if (!CBaseEntity::GetLocalPlayer()) return;

			NSDK::PlayerInfo entityInfos;
			NSDK::I::Engine()->GetPlayerInfo(pEntity->EntIndex(), &entityInfos);
			if (NSDK::I::Engine()->GetPlayerUserID(attacker) == NSDK::I::Engine()->GetLocalPlayer())
			{
				int idx = pEntity->EntIndex();
				if (hitgroup == 1)
				{
					info::shot_hit[idx] = true;
				}

				hpleft > 0 ? Drawing::DrawHitboxes(pEntity, 255, 0, 0, 255) : Drawing::DrawHitboxes(pEntity, 150, 150, 80, 160);

				fl_expire_time = NSDK::I::GlobalVars()->curtime + .75f;

				float curtime = NSDK::I::GlobalVars()->curtime;

				if (fl_expire_time >= curtime) NSDK::I::Engine()->ClientCmd_Unrestricted("play buttons\\arena_switch_press_02.wav");

				last_dmg = damage;
			}
		}
	}

	void OnPaint()
	{
		auto curtime = NSDK::I::GlobalVars()->curtime;
		auto lineSize = 8;

		if (fl_expire_time >= curtime)
		{
			int screenSizeX, screenCenterX;
			int screenSizeY, screenCenterY;

			NSDK::I::Engine()->GetScreenSize(screenSizeX, screenSizeY);

			int alpha = (fl_expire_time - curtime) * 340;

			screenCenterX = screenSizeX / 2;
			screenCenterY = screenSizeY / 2;

			NSDK::I::MatSurface()->DrawSetColor(NSDK::Color(255, 153, 51, alpha));
			NSDK::I::MatSurface()->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4));
			NSDK::I::MatSurface()->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4));
			NSDK::I::MatSurface()->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4));
			NSDK::I::MatSurface()->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4));

			Drawing::DrawString(NSDK::Color(255, 0, 0, alpha), Drawing::hStrictlyFont, std::to_string(last_dmg).c_str(), screenCenterX + 30, screenCenterY);
		}

	}

private:
	HurtListener _listener;
	float        fl_expire_time;
	int last_dmg;
};