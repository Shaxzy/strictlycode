#include "Injector.h"

int main()	
{
	CONSOLE_CURSOR_INFO curCursorInfo;
	curCursorInfo.bVisible = false;
	curCursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curCursorInfo);

	COORD CursorPosition = { static_cast<short>(8), static_cast<short>(3) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);

	std::cout << "[" << color::green << "*" << color::white << "]" << " waiting for csgo.exe...  ";

	DWORD process = process::process("csgo.exe");

	while (process == NULL)
	{
		Sleep(50);
		process = process::process("csgo.exe");
	}

	std::cout << "\b" << std::flush << "[" << color::green << "found" << color::white << "]" << std::endl;

	process::inject(process, "StrictlyCode.dll");

	Sleep(1500);
}