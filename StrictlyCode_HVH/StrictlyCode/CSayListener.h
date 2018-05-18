#include <Windows.h>
#include "SqchSDK\Interfaces.h"
#include "SqchSDK\Offsets.h"
#include "EntityStructs.h"
#include "OptionsManager.h"
#include "Utilities.h"
#include "CNotify.h"
#include "ConfigManager.h"
#pragma comment(lib, "Winmm.lib")

void handle_input(std::string input, std::vector<std::string>& vszBuffer)
{
	std::size_t nPos = 0;
	while (true)
	{
		nPos = input.find_first_of(" \n\0");
		if (nPos != std::string::npos)
		{
			vszBuffer.push_back(input.substr(0, nPos));
			input.erase(0, nPos + 1);
		}
		else
		{
			if (!input.empty())
				vszBuffer.push_back(input);
			break;
		}
	}
}

class CSayListener
{
	class SayListener : public IGameEventListener2
	{
	public:
		void start()
		{
			if (!NSDK::I::GameEvents()->AddListener(this, "player_say", true))
			{
				NSDK::I::CVar()->ConsoleColorPrintf(NSDK::Color(255, 0, 0), ("-> Failed Say Listener. \n"));
			}
			if (NSDK::I::GameEvents()->AddListener(this, "player_say", true))
			{

			}
		}
		void stop()
		{
			NSDK::I::GameEvents()->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent* event) override
		{
			CSayListener::singleton()->OnFireEvent(event);
		}
		int GetEventDebugID(void) override
		{
			return EVENT_DEBUG_ID_INIT /*0x2A*/;
		}
	};
public:
	static CSayListener* singleton()
	{
		static CSayListener* instance = new CSayListener;
		return instance;
	}

	void init()
	{
		_listener.start();
	}

	void OnFireEvent(IGameEvent* event)
	{
		if (!strcmp(event->GetName(), "player_say"))
		{
			//if (!Options.bTextSettings) return;
			return;
			//this doesnt work properly
			int playerid = event->GetInt("userid");
			if (NSDK::I::Engine()->GetPlayerUserID(playerid) == NSDK::I::Engine()->GetLocalPlayer())
			{
				//works
				const char* text = event->GetString("text");
				std::string sText = std::string(text);
				std::vector<std::string> Args;
				handle_input(sText, Args);
				
				if (Args.size() < 3) return;

				//Category Setting settingInfo DataType
				std::string strCategory = Args.at(0);
				char *cCategory = new char[strCategory.length() + 1];
				strcpy(cCategory, strCategory.c_str());

				std::string strSetting = Args.at(1);
				char *cSetting = new char[strSetting.length() + 1];
				strcpy(cSetting, strSetting.c_str());

				std::string strSettingInfo = Args.at(2);
				char *cSettingInfo = new char[strSettingInfo.length() + 1];
				strcpy(cSettingInfo, strSettingInfo.c_str());

				std::string dataType = Args.at(3);

				if (dataType == "f")
				{
					float fSettingInfo = strtof((strSettingInfo).c_str(), 0); // string to float
					ConSys->WriteFloat(cCategory, cSetting, fSettingInfo);
				}

				if (dataType == "s")
				{
					ConSys->WriteString(cCategory, cSetting, cSettingInfo);
				}

				if (dataType == "i")
				{
					float iSettingInfo = strtof((strSettingInfo).c_str(), 0); // string to float
					ConSys->WriteInt(cCategory, cSetting, iSettingInfo);
				}

				ConSys->SaveConfig();
				ConSys->LoadConfig();

				delete[] cSettingInfo;
				delete[] cSetting;
				delete[] cCategory;

				std::string changed = "set " + strCategory + " " + strSetting + "( " + dataType + " ) to: " + strSettingInfo;
				PushNotifications::Push(changed);
			}
		}
	}

private:
	SayListener _listener;
};