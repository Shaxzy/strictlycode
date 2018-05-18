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
	strcat(Path, "C:\\Iso");
	CreateDirectoryA(Path, nullptr);
	strcpy(Path2, Path);

	strcat(Path, "\\HVH1.ini");
	strcat(Path2, "\\HVH2.ini");

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

void Config::WriteString(char* Cata, char* Name, char* SetVal)
{
	WritePrivateProfileStringA(Cata, Name, SetVal, this->Handle());
}

void Config::SaveConfig()
{
	WriteInt(("Aimbot"), ("Enabled"), Options.bAimbot);
	WriteInt(("Aimbot"), ("Hitbox"), Options.iHitbox);
	WriteFloat(("Aimbot"), ("FOV"), Options.fAimbotFov);
	WriteInt(("Aimbot"), ("Hitscan"), Options.bHitscan);
	WriteFloat(("Aimbot"), ("MinDmg"), Options.fAwall);
	WriteInt(("Aimbot"), ("AutoScope"), Options.bAutoScope);
	WriteInt(("Aimbot"), ("AutoShoot"), Options.bAutoShoot);
	WriteInt(("Aimbot"), ("BacktrackLBY"), Options.bLBYBacktrack);
	WriteInt(("Aimbot"), ("LBYShoot"), Options.bLBYUpdate);
	WriteInt(("Aimbot"), ("AntiAim"), Options.iAntiAim);
	WriteInt(("Aimbot"), ("LBYType"), Options.iLBYType);
	WriteFloat(("Aimbot"), ("LBYDelta"), Options.fLBYDelta);
	WriteInt(("Aimbot"), ("Hitchance"), Options.iHitchance);
	WriteInt(("Aimbot"), ("AutoSlow"), Options.bAutoSlow);

	WriteInt(("Visuals"), ("FovRing"), Options.bFovring);
	WriteInt(("Visuals"), ("Skinchanger"), Options.bSkinchanger);
	WriteInt(("Visuals"), ("HealthBar"), Options.bHealthBar);
	WriteInt(("Visuals"), ("Box"), Options.bBoxESP);
	WriteInt(("Visuals"), ("Name"), Options.bPlayerName);
	WriteInt(("Visuals"), ("Bone"), Options.bBoneESP);
	WriteInt(("Visuals"), ("Weapon"), Options.bWeaponESP);
	WriteInt(("Visuals"), ("localFov"), Options.iLocalFov);
	WriteInt(("Visuals"), ("ResolverInfo"), Options.bResolverESP);
	WriteInt(("Visuals"), ("Tracer"), Options.iTracer);
	WriteInt(("Visuals"), ("Info"), Options.bInfoESP);

	WriteInt(("Misc"), ("Bhop"), Options.bBhop);
	WriteInt(("Misc"), ("ChatSpammer"), Options.bChatSpam);
	WriteInt(("Misc"), ("Clantag"), Options.bClantagchanger);
	WriteInt(("Misc"), ("ConfigSelection"), Options.iConfig);
	WriteInt(("Misc"), ("TrashTalk"), Options.bTrashTalk);
}

void Config::LoadConfig()
{
	Options.bAimbot = ReadInt(("Aimbot"), ("Enabled"), 0);
	Options.iHitbox = ReadInt(("Aimbot"), ("Hitbox"), 0);
	Options.fAimbotFov = ReadFloat(("Aimbot"), ("FOV"), 0);
	Options.bHitscan = ReadInt(("Aimbot"), ("Hitscan"), 0);
	Options.fAwall = ReadFloat(("Aimbot"), ("MinDmg"), 0);
	Options.bAutoScope = ReadInt(("Aimbot"), ("AutoScope"), 0);
	Options.bAutoShoot = ReadInt(("Aimbot"), ("AutoShoot"), 0);
	Options.bLBYBacktrack = ReadInt(("Aimbot"), ("BacktrackLBY"), 0);
	Options.bLBYUpdate = ReadInt(("Aimbot"), ("LBYShoot"), 0);
	Options.iAntiAim = ReadInt(("Aimbot"), ("AntiAim"), 0);
	Options.iLBYType = ReadInt(("Aimbot"), ("LBYType"), 0);
	Options.fLBYDelta = ReadFloat(("Aimbot"), ("LBYDelta"), 0);
	Options.iHitchance = ReadInt(("Aimbot"), ("Hitchance"), 0);
	Options.bAutoSlow = ReadInt(("Aimbot"), ("AutoSlow"), 0);

	Options.bFovring = ReadInt(("Visuals"), ("FovRing"), 0);
	Options.bSkinchanger = ReadInt(("Visuals"), ("Skinchanger"), 0);
	Options.bHealthBar = ReadInt(("Visuals"), ("HealthBar"), 0);
	Options.bBoxESP = ReadInt(("Visuals"), ("Box"), 0);
	Options.bPlayerName = ReadInt(("Visuals"), ("Name"), 0);
	Options.bBoneESP = ReadInt(("Visuals"), ("Bone"), 0);
	Options.bWeaponESP = ReadInt(("Visuals"), ("Weapon"), 0);
	Options.iLocalFov = ReadInt(("Visuals"), ("localFov"), 0);
	Options.bResolverESP = ReadInt(("Visuals"), ("ResolverInfo"), 0);
	Options.iTracer = ReadInt(("Visuals"), ("Tracer"), 0);
	Options.bInfoESP = ReadInt(("Visuals"), ("Info"), 0);

	Options.bBhop = ReadInt(("Misc"), ("Bhop"), 0);
	Options.bChatSpam = ReadInt(("Misc"), ("ChatSpammer"), 0);
	Options.bClantagchanger = ReadInt(("Misc"), ("Clantag"), 0);
	Options.iConfig = ReadInt(("Misc"), ("ConfigSelection"), 0);
	Options.bTrashTalk = ReadInt(("Misc"), ("TrashTalk"), 0);
}