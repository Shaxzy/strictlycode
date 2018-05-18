#include "ConfigManager.h"
#include <winerror.h>
#pragma warning( disable : 4091)
#include <ShlObj.h>
#include <string>
#include <sstream>
#include "OptionsManager.h"

#pragma region Disabling warnings

#pragma warning(disable: 4244)
#pragma warning(disable: 4800)
#pragma warning(disable: 4018)
#pragma warning(disable: 4715)

#pragma endregion

Config* ConSys = new Config();

inline bool Check(std::string File)
{
	struct stat buf;
	return (stat(File.c_str(), &buf) == 0);
}

bool Config::CheckConfigs()
{
	/*=====================================*/
	strcat(Path, "C:\\ShibaHook");
	CreateDirectoryA(Path, nullptr);
	strcpy(Path2, Path);

	strcat(Path, "\\Legit.ini");
	strcat(Path2, "\\Legit1.ini");

	return true;
}

char* Config::Handle()
{
	if (Options.iConfig == 0)
	{
			return Path;
	}

	if (Options.iConfig == 1)
	{
			return Path2;
	}
}

int Config::ReadInt(char* Cata, char* Name, int DefaultVal)
{
	int iResult;
	iResult = GetPrivateProfileIntA(Cata, Name, DefaultVal, this->Handle());
	return iResult;
}

NSDK::Color Config::ReadColor(char* Cata, char* Name, NSDK::Color DefaultVal)
{
	int r = GetPrivateProfileIntA(Cata, Name + char("r"), DefaultVal.r(), this->Handle());
	int g = GetPrivateProfileIntA(Cata, Name + char("g"), DefaultVal.g(), this->Handle());
	int b = GetPrivateProfileIntA(Cata, Name + char("b"), DefaultVal.b(), this->Handle());
	int a = GetPrivateProfileIntA(Cata, Name + char("a"), DefaultVal.a(), this->Handle());
	return NSDK::Color(r, g, b, a);
}

float Config::ReadFloat(char* Cata, char* Name, float DefaultVal)
{
	char result[255];
	char cDefault[255];
	float fresult;
	sprintf(cDefault, "%f", DefaultVal);
	GetPrivateProfileStringA(Cata, Name, cDefault, result, 255, this->Handle());
	fresult = atof(result);
	return fresult;
}

char* Config::ReadString(char* Cata, char* Name, char* DefaultVal)
{
	auto result = new char[255];
	DWORD oProtection;
	VirtualProtect(reinterpret_cast<void*>(result), 4, PAGE_READWRITE, &oProtection);
	memset(result, 0x00, 255);
	VirtualProtect(reinterpret_cast<void*>(result), 4, oProtection, &oProtection);
	GetPrivateProfileStringA(Cata, Name, DefaultVal, result, 255, this->Handle());
	return result;
}

void Config::WriteFloat(char* Cata, char* Name, float SetVal)
{
	char buf[255];
	sprintf(buf, "%f", SetVal);
	WritePrivateProfileStringA(Cata, Name, buf, this->Handle());
}

void Config::WriteInt(char* Cata, char* Name, int SetVal)
{
	char buf[255];
	sprintf(buf, "%d", SetVal);
	WritePrivateProfileStringA(Cata, Name, buf, this->Handle());
}

void Config::WriteColor(char* Cata, char* Name, NSDK::Color SetVal)
{
	char red_buff[255];
	sprintf(red_buff, "%d", SetVal.r());
	WritePrivateProfileStringA(Cata, Name + char("r"), red_buff, this->Handle());

	char green_buff[255];
	sprintf(green_buff, "%d", SetVal.g());
	WritePrivateProfileStringA(Cata, Name + char("g"), green_buff, this->Handle());

	char blue_buff[255];
	sprintf(blue_buff, "%d", SetVal.b());
	WritePrivateProfileStringA(Cata, Name + char("b"), blue_buff, this->Handle());

	char alpha_buff[255];
	sprintf(alpha_buff, "%d", SetVal.a());
	WritePrivateProfileStringA(Cata, Name + char("a"), alpha_buff, this->Handle());
}

void Config::WriteString(char* Cata, char* Name, char* SetVal)
{
	WritePrivateProfileStringA(Cata, Name, SetVal, this->Handle());
}

void Config::SaveConfig()
{
	WriteInt(("Aimbot"), ("Enabled"), Options.bAimbot);
	WriteInt(("Aimbot"), ("SmoothingEnabled"), Options.bSmoothing);
	WriteInt(("Aimbot"), ("Backtracking"), Options.bBacktracking);
	WriteInt(("Aimbot"), ("LuckShot"), Options.bLuckShot);
	WriteInt(("Aimbot"), ("Hitbox"), Options.iHitbox);
	WriteInt(("Aimbot"), ("LuckShotRate"), Options.iLuckShotRate);
	WriteFloat(("Aimbot"), ("FOV"), Options.fNormalFov);
	WriteFloat(("Aimbot"), ("Smoothing"), Options.fSmoothing);

	WriteInt(("Visuals"), ("FovRing"), Options.bFovring);
	WriteInt(("Visuals"), ("Skinchanger"), Options.bSkinchanger);
	WriteInt(("Visuals"), ("HealthBar"), Options.bHealthBar);
	WriteInt(("Visuals"), ("Box"), Options.bBoxESP);
	WriteInt(("Visuals"), ("Name"), Options.bPlayerName);
	WriteInt(("Visuals"), ("Bone"), Options.bBoneESP);
	WriteInt(("Visuals"), ("Weapon"), Options.bWeaponESP);
	WriteInt(("Visuals"), ("localFov"), Options.iLocalFov);
	WriteInt(("Visuals"), ("Sound"), Options.bSoundESP);

	WriteInt(("Misc"), ("Bhop"), Options.bBhop);
	WriteInt(("Misc"), ("ChatSpammer"), Options.bChatSpam);
	WriteInt(("Misc"), ("Clantag"), Options.bClantagchanger);
	WriteInt(("Misc"), ("ConfigSelection"), Options.iConfig);

	WriteColor("Colors", "enemy_box_color", Options.box_enemy_color);
	WriteColor("Colors", "team_box_color", Options.box_team_color);
	WriteColor("Colors", "enemy_name_color", Options.player_name_enemy_color);
	WriteColor("Colors", "team_name_color", Options.player_name_team_color);
	WriteColor("Colors", "enemy_weapon_color", Options.weapon_enemy_color);
	WriteColor("Colors", "team_weapon_color", Options.weapon_team_color);
	WriteColor("Colors", "fov_ring_color", Options.fov_ring_color);
}

void Config::LoadConfig()
{
	Options.bAimbot = ReadInt(("Aimbot"), ("Enabled"), 0);
	Options.bSmoothing = ReadInt(("Aimbot"), ("SmoothingEnabled"), 0);
	Options.bBacktracking = ReadInt(("Aimbot"), ("Backtracking"), 0);
	Options.bLuckShot = ReadInt(("Aimbot"), ("LuckShot"), 0);
	Options.iHitbox = ReadInt(("Aimbot"), ("Hitbox"), 0);
	Options.iLuckShotRate = ReadInt(("Aimbot"), ("LuckShotRate"), 0);
	Options.fNormalFov = ReadFloat(("Aimbot"), ("FOV"), 0);
	Options.fSmoothing = ReadFloat(("Aimbot"), ("Smoothing"), 0);

	Options.bFovring = ReadInt(("Visuals"), ("FovRing"), 0);
	Options.bSkinchanger = ReadInt(("Visuals"), ("Skinchanger"), 0);
	Options.bHealthBar = ReadInt(("Visuals"), ("HealthBar"), 0);
	Options.bBoxESP = ReadInt(("Visuals"), ("Box"), 0);
	Options.bPlayerName = ReadInt(("Visuals"), ("Name"), 0);
	Options.bBoneESP = ReadInt(("Visuals"), ("Bone"), 0);
	Options.bWeaponESP = ReadInt(("Visuals"), ("Weapon"), 0);
	Options.iLocalFov = ReadInt(("Visuals"), ("localFov"), 0);
	Options.bSoundESP = ReadInt(("Visuals"), ("Sound"), 0);

	Options.bBhop = ReadInt(("Misc"), ("Bhop"), 0);
	Options.bChatSpam = ReadInt(("Misc"), ("ChatSpammer"), 0);
	Options.bClantagchanger = ReadInt(("Misc"), ("Clantag"), 0);
	Options.iConfig = ReadInt(("Misc"), ("ConfigSelection"), 0);

	Options.box_enemy_color = ReadColor("Colors", "enemy_box_color", NSDK::Color(255,255,255,255));
	Options.box_team_color = ReadColor("Colors", "team_box_color", NSDK::Color(255, 255, 255, 255));
	Options.player_name_enemy_color = ReadColor("Colors", "enemy_name_color", NSDK::Color(255, 255, 255, 255));
	Options.player_name_team_color = ReadColor("Colors", "team_name_color", NSDK::Color(255, 255, 255, 255));
	Options.weapon_enemy_color = ReadColor("Colors", "enemy_weapon_color", NSDK::Color(255, 255, 255, 255));
	Options.weapon_team_color = ReadColor("Colors", "team_weapon_color", NSDK::Color(255, 255, 255, 255));
	Options.fov_ring_color = ReadColor("Colors", "fov_ring_color", NSDK::Color(255, 255, 255, 255));
}