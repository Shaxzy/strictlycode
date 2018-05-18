#include <Windows.h>
#include "MacProtect.h"
#include "Hooks.h"
#include "Globals.h"
void MainThread() 
{
	Hooks::Initialize();
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
			FreeLibraryAndExitThread(hinstDLL, 0); //FreeLibAndStopThread
		}
		Sleep(3000);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hinstDLL);
		
		char* local_mac = Mac::get_mac();
		/*std::string user;

		std::ifstream infile;
		infile.open("C:\\Iso\\user.txt");

		while (!(infile.eof()))
		{
			getline(infile, user);
			std::cout << user;
		}

		infile.close();
		//using G::Username causes crashes
		G::username = user.c_str();
		remove("C:\\Iso\\user.txt");
		*/
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UnHookThread, hinstDLL, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hinstDLL, 0, 0);
		break;
	}
	case DLL_PROCESS_DETACH:
		Hooks::RestoreAllTable();
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}