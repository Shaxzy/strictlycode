#include "Injector.h"

int main()	
{

	DWORD process = process::find("csgo.exe");
	while (process == NULL)
	{
		Sleep(50);
		process = process::find("csgo.exe");
	}

	process::inject(process, "ShibaHook.dll");

	std::cout << "injection finished! (ShibaHook.dll)"<< std::endl;

	Sleep(1000);
}