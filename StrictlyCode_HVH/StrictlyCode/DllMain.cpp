#include <Windows.h>
#include "MacProtect.h"
#include "Hooks.h"
#include "Globals.h"
#define null_user "68:1C:A2:07:4C:41FBI-2"
#define veno_user "DC:85:DE:FF:FE:EFPC"
void MainThread() 
{
	Hooks::Initialize();
}

char* getMachineName()
{
	static char computerName[1024];
	DWORD size = 1024;
	GetComputerName(computerName, &size);
	return &(computerName[0]);
}

bool file_is_good(const char *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void UnHookThread(HINSTANCE hinstDLL) 
{
	while (true) 
	{
		if (GetAsyncKeyState(VK_END) & 0x1) 
		{ 
			//Press END to detach DLL
			Hooks::RestoreAllTable();
			Sleep(5000);
			FreeLibrary(hinstDLL); //FreeLib
		}
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		while (!GetModuleHandleA("serverbrowser.dll")) Sleep(50);

		DisableThreadLibraryCalls(hinstDLL);
		
		char* localMac = Mac::get_mac();
		std::string big = localMac + std::string(getMachineName());
		if(big != null_user && big != veno_user)
		{
			Local::user = big;
		}
		if(big == null_user)
		{
			Local::user = "jukebox";
		}
		if(big == veno_user)
		{
			Local::user = "veno";
		}
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UnHookThread, hinstDLL, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hinstDLL, 0, 0);
		break;
	}
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}