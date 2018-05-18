#pragma once

#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"
#include "EntityStructs.h"
#include "OptionsManager.h"
#include "Utilities.h"
#include "DrawManager.h"
#include "CNotify.h"

class CPurchaseListener
{
	class PurchaseListener : IGameEventListener2
	{
	public:
		void start()
		{
			if (!NSDK::I::GameEvents()->AddListener(this, "item_purchase", false))
			{
				NSDK::I::CVar()->ConsoleColorPrintf(NSDK::Color(0, 255, 0), ("-> Failed item_purchase. \n"));
			}
			if (NSDK::I::GameEvents()->AddListener(this, "item_purchase", false))
			{
			}
		}
		void stop()
		{
			NSDK::I::GameEvents()->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent* event) override
		{
			CPurchaseListener::singleton()->OnFireEvent(event);
		}
		int GetEventDebugID(void) override
		{
			return EVENT_DEBUG_ID_INIT /*0x2A*/;
		}
	};
public:
	static CPurchaseListener* singleton()
	{
		static CPurchaseListener* instance = new CPurchaseListener();
		return instance;
	}

	void init()
	{
		_listener.start();
	}

	void OnFireEvent(IGameEvent* event)
	{
		auto local = CBaseEntity::GetLocalPlayer();
		if (!strcmp(event->GetName(), "item_purchase"))
		{
			auto buyer = event->GetInt("userid");
			std::string gun = event->GetString("weapon");

			if (strstr(gun.c_str(), "molotov")
				|| strstr(gun.c_str(), "nade")
				|| strstr(gun.c_str(), "kevlar")
				|| strstr(gun.c_str(), "decoy")
				|| strstr(gun.c_str(), "suit")
				|| strstr(gun.c_str(), "flash")
				|| strstr(gun.c_str(), "vest")
				|| strstr(gun.c_str(), "cutter")
				|| strstr(gun.c_str(), "defuse")
				)  return;
			auto player_index = NSDK::I::Engine()->GetPlayerUserID(buyer);
			CBaseEntity* player = (CBaseEntity*)NSDK::I::EntityList()->GetClientEntity(player_index);
			NSDK::PlayerInfo pinfo;

			if (player && local && (player->GetTeamNum() != local->GetTeamNum()) && NSDK::I::Engine()->GetPlayerInfo(player_index, &pinfo))
			{
			}
		}
	}


private:
	PurchaseListener _listener;
};